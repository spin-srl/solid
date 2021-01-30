cmake_minimum_required(VERSION 3.1)

set(TARGET_OS \"${CMAKE_SYSTEM_NAME}\")

if (TARGET_OS STREQUAL "\"\"")
    set(TARGET_OS "linux")
endif()

set(PROJECT_NAME "SolidFLTK-${TARGET_OS}" )

project(${PROJECT_NAME})

FILE(GLOB SRCS "src/*.cpp" "src/*.cxx")

#message("TARGET_OS = '${CMAKE_SYSTEM_NAME}'")
add_library(${PROJECT_NAME} ${SRCS})

add_executable(app ${SRCS} tests/tests.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "include")
target_include_directories(app PUBLIC "include")

target_link_libraries(app fltk
                                        X11
                                        Xext
                                        Xfixes
                                        Xrender
                                        Xft
                                        fontconfig
                                        dl
                                        pthread)

target_link_libraries(app ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

install (FILES "include/Solid.h"
        DESTINATION include)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Targets.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake
)
