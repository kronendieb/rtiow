set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp app.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder 
    PUBLIC Window 
    PUBLIC Shader 
    PUBLIC ext/glfw/include
    PUBLIC ext/glew/include
    PUBLIC ext/glm)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE Window
    PRIVATE Shader
    PRIVATE ext/glfw/src
    PRIVATE ext/glew/lib
    PRIVATE ext/glm)

target_link_libraries(${PROJECT_NAME} glfw libglew_static opengl32 glm adder window shader)

add_subdirectory(Adder)
add_subdirectory(Window)
add_subdirectory(Shader)
