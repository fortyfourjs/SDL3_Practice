cmake_minimum_required(VERSION 3.16)
project(SDL3_Practice C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)

# Descarca si compileaza SDL3
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(SDL3)

# Dezactiveaza AVIF/dav1d 
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TESTS OFF CACHE BOOL "" FORCE)

# Descarca si compileaza SDL3_image
FetchContent_Declare(
    SDL3_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG        main
)
FetchContent_MakeAvailable(SDL3_image)

# Sursa si executabil
add_executable(SDL3_Practice
    main.cpp
    board.h
    board.cpp
)

# Legare biblioteci
target_link_libraries(SDL3_Practice PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
)