cmake_minimum_required(VERSION 3.30)
project(roulette)

set(CMAKE_CXX_STANDARD 20)

add_executable(roulette main.cpp
        Player.cpp
        Player.hpp
        Money.cpp
        Money.hpp
        Field.hpp
        Wheel.hpp
        Wheel.cpp
        AmericanWheel.cpp
        AmericanWheel.hpp
        EuropeanWheel.cpp
        EuropeanWheel.hpp
        Game.cpp
        Game.hpp
        common.hpp)
