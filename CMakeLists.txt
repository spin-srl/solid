cmake_minimum_required(VERSION 3.1)

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("user32.h" IS_WIN)

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

target_compile_definitions(app PUBLIC FLTK_HAVE_CAIRO)

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(app PUBLIC "include")

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
    target_link_libraries(app
            /Shine/solid/libfltk.a
            winpthread
            ole32
            uuid
            comctl32
            comdlg32
            ws2_32)
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
