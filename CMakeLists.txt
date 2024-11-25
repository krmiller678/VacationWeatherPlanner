cmake_minimum_required(VERSION 3.29)
project(VacationWeatherPlanner)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(VacationWeatherPlanner
    CitiesOfInterest.cpp
    CitiesOfInterest.h
    City.cpp
    City.h
    main.cpp
    stuff.h
    WeatherDataNode.cpp
    WeatherDataNode.h)
