
add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder 
    PUBLIC ext/glfw/include
    PUBLIC ext/glm)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE ext/glfw/src
    PRIVATE ext/glm)


add_subdirectory(Adder)

target_link_libraries(${PROJECT_NAME} adder glfw opengl32 glm)