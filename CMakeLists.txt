cmake_minimum_required(VERSION 3.28)
project(FacchiniGames)

set(CMAKE_CXX_STANDARD 17)

add_executable(FacchiniGames src/main.cpp
        include/hangman.h
        src/hangman.cpp
        include/colors.h
        include/misc.h
        src/misc.cpp
        include/tictactoe.h
        src/tictactoe.cpp)
