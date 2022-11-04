CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

PROJECT(para_config)

set(CMAKE_BUILD_TYPE Debug )

# include_directories(./lib/)

add_executable(main main.cpp ./lib/include.cpp)