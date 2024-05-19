cmake_minimum_required(VERSION 3.10)
project(MazeRun)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(MazeRun
        src/main.c
        src/keyboard.c
        src/screen.c
        src/timer.c
)