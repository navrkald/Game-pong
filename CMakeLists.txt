cmake_minimum_required(VERSION 3.2)
project(pong)

find_package(wxWidgets COMPONENTS core base REQUIRED)
include( "${wxWidgets_USE_FILE}" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories(/usr/include/wx-3.0/)
set(SOURCE_FILES main.cpp)
add_executable(pong ${SOURCE_FILES} Ball.cpp Ball.h Pong.cpp Pong.h Paddle.cpp Paddle.h AI.cpp AI.h)

target_link_libraries(
    pong
    ${wxWidgets_LIBRARIES}
    )