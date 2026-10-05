cmake_minimum_required(VERSION 3.16)
project(Test_windows C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(SDL3_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/cmake" CACHE PATH "Path to SDL3 CMake config" FORCE)
endif()

find_package(SDL3 REQUIRED)

#adauga fisiere noi
add_executable(SDL3_Practice
    main.cpp
    board.h
    board.cpp
)

target_link_libraries(SDL3_Practice PRIVATE SDL3::SDL3)

if(WIN32)
    add_custom_command(TARGET SDL3_Practice POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL3/lib/x64/SDL3.dll"
        $<TARGET_FILE_DIR:SDL3_Practice>
    )
endif()