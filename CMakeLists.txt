cmake_minimum_required(VERSION 3.19)
project(pomotimer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Multimedia)

qt_standard_project_setup()

#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/utils
    ${CMAKE_SOURCE_DIR}/include/pages
)

qt_add_executable(pomotimer
    WIN32 MACOSX_BUNDLE
    resources/pomo.qrc
    # utilities
    src/utils/settings.cpp
    src/utils/ringtone.cpp
    # pages
    src/pages/page_settings_timer.cpp
    src/pages/page_settings.cpp
    src/pages/page_main.cpp
    # ui components
    src/ui/text_label_input.cpp
    src/ui/clickable_label.cpp
    src/ui/text_label_link.cpp
    src/ui/action_button.cpp
    src/ui/clock_face.cpp
    src/ui/text_label.cpp
    src/ui/menu_page.cpp
    src/ui/window.cpp
    src/ui/input.cpp
    src/ui/page.cpp
    # main files
    src/widget_window.cpp
    src/device.cpp
    src/timer.cpp
    src/main.cpp

    ## headers:
    # utilities
    include/utils/state_manager.h
    include/utils/ringtone.h
    include/utils/settings.h
    # pages
    include/pages/page_settings_timer.h
    include/pages/page_settings.h
    include/pages/page_main.h
    # ui components
    include/ui/text_label_input.h
    include/ui/clickable_label.h
    include/ui/text_label_link.h
    include/ui/action_button.h
    include/ui/clock_face.h
    include/ui/text_label.h
    include/ui/menu_page.h
    include/ui/window.h
    include/ui/input.h
    include/ui/page.h
    # main files
    include/widget_window.h
    include/device.h
    include/timer.h

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
