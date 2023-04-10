cmake_minimum_required(VERSION 3.8)

project(warzone)

add_library(
  stuff
  CommandProcessor.h
  CommandProcessor.cpp
)

add_executable(warzone CommandProcessorDriver.cpp)

target_link_libraries(warzone PRIVATE stuff)