cmake_minimum_required(VERSION 3.19)
project(pomotimer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

include_directories(${CMAKE_SOURCE_DIR}/include)

qt_add_executable(pomotimer
    WIN32 MACOSX_BUNDLE
    ui/timer.ui
    resources/pomo.qrc
    include/clock_face.h
    include/clickable_label.h
    include/circular_progress_bar.h
    include/timer.h
    include/action_button.h
    include/timer_page.h
    include/widget_window.h
    src/main.cpp
    src/clock_face.cpp
    src/action_button.cpp
    src/circular_progress_bar.cpp
    src/clickable_label.cpp
    src/timer.cpp
    src/timer_page.cpp
    src/widget_window.cpp
)

target_link_libraries(pomotimer
        PRIVATE
        Qt::Core
        Qt::Widgets
        sqlite3
        Qt::Multimedia
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
