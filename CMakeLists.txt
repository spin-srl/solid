cmake_minimum_required(VERSION 3.1)

include(CheckIncludeFile)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(IS_WIN False)
else ()
    set(IS_WIN True)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_FOR_WINDOWS "Build for windows")

if (IS_WIN OR BUILD_FOR_WINDOWS)
    set(TARGET_OS "windows")
else ()
    set(TARGET_OS "linux")
endif ()

set(PROJECT_NAME "Solid")

project(${PROJECT_NAME})

FILE(GLOB SRCS "src/*.cpp" "src/*.cxx")

add_library(${PROJECT_NAME} ${SRCS})

add_executable(app ${SRCS} tests/tests.cpp)

add_compile_definitions(FLTK_HAVE_CAIRO=1)

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(app PUBLIC "include")

message("Building for " ${TARGET_OS})

if (TARGET_OS STREQUAL "linux")
#    include_directories("/usr/include/cairo")
    target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include/cairo")
    target_include_directories(${PROJECT_NAME} PUBLIC "/usr/local/include")
    target_link_libraries(app fltk fltk_cairo
            X11
            Xext
            #            Xfixes
            Xrender
            #            Xft
            fontconfig
            dl
            pthread
            cairo
            )
else ()
    if (IS_WIN)
        include("C:/Program Files (x86)/FLTK/CMake/FLTKConfig.cmake")
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
    else ()
        include("/media/Datos/Softwares/development/FLTK/fltk-windows-debug/FLTKConfig.cmake")

        target_link_libraries(app
                fltk
                fltk_cairo
                )
        message("INCLUDES: " ${FLTK_INCLUDE_DIRS})
        include_directories(${FLTK_INCLUDE_DIRS})
    endif ()
endif ()

target_link_libraries(app ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

FILE(GLOB SOLID_INCLUDES include/*.h)

install(FILES ${SOLID_INCLUDES}
        DESTINATION include)

install(EXPORT ${PROJECT_NAME}Targets
        FILE SolidTargets.cmake
        NAMESPACE Solid::
        DESTINATION lib/cmake
        )
