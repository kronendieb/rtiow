cmake_minimum_required(VERSION 3.0.0)

project(RTIOW)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC Adder)
target_link_directories(${PROJECT_NAME} PRIVATE Adder)

add_subdirectory(Adder)

target_link_libraries(${PROJECT_NAME} adder)
