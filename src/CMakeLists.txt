set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp app.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Adder 
    PUBLIC Window 
    PUBLIC ext/glfw/include
    PUBLIC ext/glm)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Adder
    PRIVATE Window
    PRIVATE ext/glfw/src
    PRIVATE ext/glm)

target_link_libraries(${PROJECT_NAME} glfw opengl32 glm adder window )

add_subdirectory(Adder)
add_subdirectory(Window)
