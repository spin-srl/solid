cmake_minimum_required(VERSION 3.1)

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("user32.h" IS_WIN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_FOR_WINDOWS "Build for windows")

if (IS_WIN OR BUILD_FOR_WINDOWS)
    set(TARGET_OS "windows")
else ()
    set(TARGET_OS "linux")
endif ()

set(PROJECT_NAME "Solid-${TARGET_OS}")

project(${PROJECT_NAME})

FILE(GLOB SRCS "src/*.cpp" "src/*.cxx")

add_library(${PROJECT_NAME} ${SRCS})

add_executable(app ${SRCS} tests/tests.cpp)

add_compile_definitions(FLTK_HAVE_CAIRO=1)

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(app PUBLIC "include")

message("Building for " ${TARGET_OS})

if (TARGET_OS STREQUAL "linux")
    target_include_directories(app PUBLIC "/usr/include/cairo")
    target_link_libraries(app fltk
            X11
            Xext
            Xfixes
            Xrender
            Xft
            fontconfig
            dl
            pthread
            cairo
            )
else ()
    include("C:/Program Files (x86)/FLTK/CMake/FLTKConfig.cmake" )
    target_link_directories(app PUBLIC "G:/msys64/mingw64/lib/")
    target_link_directories(app PUBLIC "G:/msys64/mingw64/bin/")

    target_link_libraries(app
            fltk
            fltk_cairo
            winpthread
            ole32
            uuid
            comctl32
            comdlg32
            ws2_32
            )

    include_directories(${FLTK_INCLUDE_DIRS})
    include_directories(G:/msys64/mingw64/include/cairo)
endif ()

target_link_libraries(app ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES "include/Solid.h"
        DESTINATION include)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake
        )
