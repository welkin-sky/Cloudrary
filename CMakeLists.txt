cmake_minimum_required(VERSION 3.16)

project(Cloudrary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick Core)

qt_standard_project_setup()

set(CMAKE_AUTORCC ON)

#遍历所有Cpp文件
file(GLOB_RECURSE CPP_FILES *.cpp *.h *.hpp)
foreach(filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND sources_files ${filename})
endforeach(filepath)

#遍历所有qml文件
file(GLOB_RECURSE QML_PATHS *.qml)
foreach(filepath ${QML_PATHS})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND qml_files ${filename})
endforeach(filepath)

#遍历所有资源文件
file(GLOB_RECURSE RES_PATHS *.png *.jpg *.svg *.ico *.ttf *.webp qmldir)
foreach(filepath ${RES_PATHS})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND resource_files ${filename})
endforeach(filepath)

#添加可执行文件
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    qt_add_executable(appCloudrary
        ${sources_files}
        Cloudrary.qrc
    )
else ()
    qt_add_executable(appCloudrary
        ${sources_files}
    )
endif ()

qt_add_qml_module(appCloudrary
    URI Cloudrary
    VERSION 1.0
    QML_FILES ${qml_files}
    RESOURCES ${resource_files}
)

target_include_directories(appCloudrary PUBLIC ./src/include ./src)

set_target_properties(appCloudrary PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appCloudrary
    PRIVATE
    Qt6::Quick
    Qt6::Core
)

install(TARGETS appCloudrary
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
