cmake_minimum_required(VERSION 3.20)

project(DynamicSpot VERSION 0.3.1 LANGUAGES CXX)

include_directories(3rdParty/spdlog/include)

add_subdirectory(src)
add_subdirectory(3rdParty/spdlog)

