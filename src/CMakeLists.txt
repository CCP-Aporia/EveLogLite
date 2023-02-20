# Generated from LogLite.pro.

cmake_minimum_required(VERSION 3.21)
project(LogLite VERSION 1.4.3 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Qt is statically linked, which defaults to not exposing any public symbols.
# Therefore, LogLite's visibility preset needs to be `hidden` as well to avoid linker warnings about
# direct access to global weak symbols.
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(NOT DEFINED INSTALL_EXAMPLESDIR)
    set(INSTALL_EXAMPLESDIR "examples")
endif()

set(INSTALL_EXAMPLEDIR "${INSTALL_EXAMPLESDIR}")

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Sql Widgets)

set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/LogLite_resource.rc")

qt_add_executable(LogLite WIN32 MACOSX_BUNDLE
    abstractlogmodel.cpp abstractlogmodel.h
    filter.ui
    filtercondition.cpp filtercondition.h
    filterconditions.cpp filterconditions.h
    filterdialog.cpp filterdialog.h
    filterhighlight.cpp filterhighlight.h filterhighlight.ui
    fixedheader.cpp fixedheader.h
    highlightdialog.cpp highlightdialog.h
    highlights.ui
    logfilter.cpp logfilter.h
    logmap.cpp logmap.h
    logmodel.cpp logmodel.h
    logmonitorfilemodel.cpp logmonitorfilemodel.h
    logstatistics.cpp logstatistics.h logstatistics.ui
    logview.cpp logview.h
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    overlaylayout.cpp overlaylayout.h
    settingsdialog.cpp settingsdialog.h settingsdialog.ui
    ${app_icon_resource_windows}
)

if(NOT GIT_FOUND)
    find_package(Git)
endif()
if(GIT_FOUND)
    get_target_property(TARGET_SOURCE_DIR LogLite SOURCE_DIR)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${TARGET_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
    message(WARNING "Git was not found, version information will not contain git details")
endif()
if(NOT GIT_COMMIT_HASH)
    set(GIT_COMMIT_HASH "Unknown commit")
endif()

target_compile_definitions(LogLite PUBLIC
    APP_VERSION="${CMAKE_PROJECT_VERSION}"
    GIT_VERSION="${GIT_COMMIT_HASH}"
)

target_link_libraries(LogLite PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Sql
    Qt::Widgets
)

# Resources:
set_source_files_properties("resources/Counter.png"
    PROPERTIES QT_RESOURCE_ALIAS "counter"
)
set_source_files_properties("resources/Error.png"
    PROPERTIES QT_RESOURCE_ALIAS "error"
)
set_source_files_properties("resources/Fatal.png"
    PROPERTIES QT_RESOURCE_ALIAS "fatal"
)
set_source_files_properties("resources/Info.png"
    PROPERTIES QT_RESOURCE_ALIAS "info"
)
set_source_files_properties("resources/Mcall.png"
    PROPERTIES QT_RESOURCE_ALIAS "machocall"
)
set_source_files_properties("resources/Notice.png"
    PROPERTIES QT_RESOURCE_ALIAS "notice"
)
set_source_files_properties("resources/Overlap.png"
    PROPERTIES QT_RESOURCE_ALIAS "overlap"
)
set_source_files_properties("resources/Warning.png"
    PROPERTIES QT_RESOURCE_ALIAS "warning"
)
set_source_files_properties("resources/filter-off.png"
    PROPERTIES QT_RESOURCE_ALIAS "nofilter"
)
set_source_files_properties("resources/filter.png"
    PROPERTIES QT_RESOURCE_ALIAS "filter"
)
set_source_files_properties("resources/highlights-off.png"
    PROPERTIES QT_RESOURCE_ALIAS "nohighlights"
)
set_source_files_properties("resources/highlights.png"
    PROPERTIES QT_RESOURCE_ALIAS "highlights"
)
set_source_files_properties("resources/pulse.png"
    PROPERTIES QT_RESOURCE_ALIAS "pulse"
)
set_source_files_properties("resources/searchClose.png"
    PROPERTIES QT_RESOURCE_ALIAS "searchClose"
)
set_source_files_properties("resources/searchDown.png"
    PROPERTIES QT_RESOURCE_ALIAS "searchDown"
)
set_source_files_properties("resources/searchUp.png"
    PROPERTIES QT_RESOURCE_ALIAS "searchUp"
)
set(resources_resource_files
    "resources/Counter.png"
    "resources/Error.png"
    "resources/Fatal.png"
    "resources/Info.png"
    "resources/Mcall.png"
    "resources/Notice.png"
    "resources/Overlap.png"
    "resources/Warning.png"
    "resources/filter-off.png"
    "resources/filter.png"
    "resources/highlights-off.png"
    "resources/highlights.png"
    "resources/pulse.png"
    "resources/searchClose.png"
    "resources/searchDown.png"
    "resources/searchUp.png"
)

qt6_add_resources(LogLite "resources"
    PREFIX
        "/default"
    FILES
        ${resources_resource_files}
)

if(APPLE)
    set(ICONSET "${CMAKE_BINARY_DIR}/icon.icns")
    execute_process(
        COMMAND_ERROR_IS_FATAL ANY
        COMMAND_ECHO STDOUT
        OUTPUT_FILE ${CMAKE_BINARY_DIR}/icon-generation-output.log
        ERROR_FILE ${CMAKE_BINARY_DIR}/icon-generation-error.log
        COMMAND iconutil -c icns -o ${ICONSET} ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.iconset
    )
    set(MACOSX_BUNDLE_ICON_FILE icon.icns)
    set_source_files_properties(${ICONSET} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
    target_sources(LogLite PUBLIC ${ICONSET})
endif()

install(TARGETS LogLite
    RUNTIME DESTINATION "${INSTALL_EXAMPLEDIR}"
    BUNDLE DESTINATION "${INSTALL_EXAMPLEDIR}"
    LIBRARY DESTINATION "${INSTALL_EXAMPLEDIR}"
)
