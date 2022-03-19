cmake_minimum_required(VERSION 3.0.0)

project(RTIOW VERSION 0.1.0 LANGUAGES C C++)

add_executable(${PROJECT_NAME} src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC Adder)
target_link_directories(${PROJECT_NAME} PRIVATE Adder)

add_subdirectory(Adder)
add_subdirectory(ext/glfw)

target_link_libraries(${PROJECT_NAME} adder)