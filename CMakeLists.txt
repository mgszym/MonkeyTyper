cmake_minimum_required(VERSION 3.27)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

#fmt
include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG 10.2.1
)

FetchContent_MakeAvailable(fmt)

#sfml
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

add_executable(Game GameEngine.cpp
        Menu.cpp
        Menu.h
        Utilities.h
        Utilities.cpp
        Game.cpp
        Game.h
        Options.cpp
        Options.h
        End.h
        End.cpp
        Scoreboard.h
        Scoreboard.h
        Scorebaord.cpp
)

target_link_libraries(Game fmt sfml-graphics)
