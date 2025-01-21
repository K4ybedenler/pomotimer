cmake_minimum_required(VERSION 3.19)
project(pomotimer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/utils
)

qt_add_executable(pomotimer
    WIN32 MACOSX_BUNDLE
    resources/pomo.qrc
    src/utils/page_controller.cpp
    src/ui/clock_face.cpp
    src/ui/action_button.cpp
    src/ui/circular_progress_bar.cpp
    src/ui/clickable_label.cpp
    src/ui/timer_page.cpp
    src/ui/page.cpp
    src/main.cpp
    src/timer.cpp
    src/main_page.cpp
    src/widget_window.cpp
    src/utils/ringtone.cpp

    include/utils/page_controller.h
    include/ui/clock_face.h
    include/ui/action_button.h
    include/ui/circular_progress_bar.h
    include/ui/clickable_label.h
    include/ui/timer_page.h
    include/ui/page.h
    include/main_page.h
    include/widget_window.h
    include/timer.h
    include/utils/ringtone.h
)

target_link_libraries(pomotimer
        PRIVATE
        Qt::Multimedia
        Qt::Core
        Qt::Widgets
        sqlite3
)

include(GNUInstallDirs)

install(TARGETS pomotimer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET pomotimer
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
