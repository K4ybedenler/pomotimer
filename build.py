#!/usr/bin/env python3

import glob
import os
import shutil
import subprocess
import sys
from pathlib import Path


def run_cmd(cmd, env=None):
    print(f"-> {' '.join(str(c) for c in cmd)}")
    try:
        subprocess.run(cmd, check=True, env=env)
    except FileNotFoundError:
        sys.exit(f"error: '{cmd[0]}' not found on PATH")


def find_qt_windows():
    """locate a Qt6 MinGW kit plus its bundled MinGW compiler and Ninja."""
    if "QT_DIR" in os.environ:
        qt_dir = Path(os.environ["QT_DIR"])
    else:
        candidates = sorted(glob.glob(r"C:\Qt\*\mingw_64"), reverse=True)
        if not candidates:
            return None
        qt_dir = Path(candidates[0])

    if not (qt_dir / "lib" / "cmake" / "Qt6" / "Qt6Config.cmake").exists():
        return None

    qt_root = qt_dir.parent.parent

    mingw_candidates = sorted(
        glob.glob(str(qt_root / "Tools" / "mingw*_64" / "bin" / "g++.exe")),
        reverse=True,
    )
    ninja_exe = qt_root / "Tools" / "Ninja" / "ninja.exe"

    return {
        "qt_dir": qt_dir,
        "mingw_bin": Path(mingw_candidates[0]).parent if mingw_candidates else None,
        "ninja_bin": ninja_exe.parent if ninja_exe.exists() else None,
    }


def find_vcpkg():
    """locate a vcpkg checkout via VCPKG_ROOT, PATH, or common install spots."""
    if "VCPKG_ROOT" in os.environ:
        root = Path(os.environ["VCPKG_ROOT"])
        if (root / "scripts" / "buildsystems" / "vcpkg.cmake").exists():
            return root

    vcpkg_exe = shutil.which("vcpkg")
    if vcpkg_exe:
        root = Path(vcpkg_exe).resolve().parent
        if (root / "scripts" / "buildsystems" / "vcpkg.cmake").exists():
            return root

    for candidate in (r"C:\vcpkg", r"C:\src\vcpkg", str(Path.home() / "vcpkg")):
        root = Path(candidate)
        if (root / "scripts" / "buildsystems" / "vcpkg.cmake").exists():
            return root

    return None


def setup_windows(env):
    print("Windows setup: locating Qt6 (MinGW kit) and vcpkg...")

    qt = find_qt_windows()
    if not qt:
        sys.exit(
            "could not find a Qt6 MinGW kit under C:\\Qt\\*\\mingw_64.\n"
            "set QT_DIR to your kit path (e.g. C:\\Qt\\6.11.2\\mingw_64) and retry."
        )
    print(f"  Qt:    {qt['qt_dir']}")
    env["QT_DIR"] = str(qt["qt_dir"])

    path_prepend = []
    if qt["mingw_bin"]:
        print(f"  MinGW: {qt['mingw_bin']}")
        path_prepend.append(str(qt["mingw_bin"]))
    if qt["ninja_bin"]:
        print(f"  Ninja: {qt['ninja_bin']}")
        path_prepend.append(str(qt["ninja_bin"]))
    if path_prepend:
        env["PATH"] = os.pathsep.join(path_prepend) + os.pathsep + env["PATH"]

    vcpkg_root = find_vcpkg()
    if not vcpkg_root:
        sys.exit(
            "could not find a vcpkg checkout.\n"
            "set VCPKG_ROOT to its path (e.g. C:\\vcpkg) and retry."
        )
    print(f"  vcpkg: {vcpkg_root}")
    env["VCPKG_ROOT"] = str(vcpkg_root)

    env.setdefault("VCPKG_TARGET_TRIPLET", "x64-mingw-dynamic")


def setup_unix(env, triplet):
    if "VCPKG_ROOT" not in env:
        vcpkg_root = find_vcpkg()
        if vcpkg_root:
            env["VCPKG_ROOT"] = str(vcpkg_root)

    if "QT_DIR" not in env:
        sys.exit("set QT_DIR to your Qt6 kit path (e.g. ~/Qt/6.11.2/gcc_64) and retry.")
    if "VCPKG_ROOT" not in env:
        sys.exit("could not find vcpkg. Set VCPKG_ROOT to its path and retry.")

    print(f"  Qt:    {env['QT_DIR']}")
    print(f"  vcpkg: {env['VCPKG_ROOT']}")
    env.setdefault("VCPKG_TARGET_TRIPLET", triplet)


def link_exe(target, link_path):
    """POSIX only: point link_path at target via a symlink (Linux/macOS
    don't gate symlink creation behind admin/Developer Mode the way
    Windows does, so this is reliable there)."""
    if link_path.is_symlink() or link_path.exists():
        link_path.unlink()
    link_path.symlink_to(target)
    print(f"\nLinked: {link_path} -> {target}")


def create_windows_shortcut(target, link_path):
    """Create a .lnk pointing at target via the WScript.Shell COM object,
    run through PowerShell so no extra Python packages are needed. Unlike
    a symlink, this needs no special privileges, and since it launches the
    target by its own real path, Windows resolves its DLLs from the
    target's directory automatically."""
    target = target.resolve()
    working_dir = target.parent

    ps_script = (
        "$ws = New-Object -ComObject WScript.Shell; "
        f'$s = $ws.CreateShortcut("{link_path.resolve()}"); '
        f'$s.TargetPath = "{target}"; '
        f'$s.WorkingDirectory = "{working_dir}"; '
        f'$s.IconLocation = "{target},0"; '
        "$s.Save()"
    )
    subprocess.run(
        ["powershell", "-NoProfile", "-Command", ps_script], check=True
    )
    print(f"\nShortcut: {link_path} -> {target}")


def main():
    os_name = sys.platform
    env = os.environ.copy()

    if os_name == "win32":
        setup_windows(env)
    elif os_name == "darwin":
        print("macOS setup: locating Qt6 and vcpkg...")
        setup_unix(env, "x64-osx")
    elif os_name.startswith("linux"):
        print("Linux setup: locating Qt6 and vcpkg...")
        setup_unix(env, "x64-linux")

    run_cmd(["cmake", "--preset", "default"], env=env)
    run_cmd(["cmake", "--build", "--preset", "default"], env=env)

    deploy_dir = Path("build") / "deploy"
    run_cmd(["cmake", "--install", "build", "--prefix", str(deploy_dir)], env=env)

    if os_name == "win32":
        create_windows_shortcut(
            deploy_dir / "bin" / "pomotimer.exe", Path("pomotimer.lnk")
        )
    else:
        link_exe(deploy_dir / "bin" / "pomotimer", Path("pomotimer"))


if __name__ == "__main__":
    main()
