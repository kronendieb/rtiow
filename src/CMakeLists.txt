set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp app.cpp)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Graphics 
    PUBLIC ext/glfw/include
    PUBLIC ext/glew/include
    PUBLIC ext/glm)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Graphics
    PRIVATE ext/glfw/src
    PRIVATE ext/glew/lib
    PRIVATE ext/glm)

target_link_libraries(${PROJECT_NAME} glfw libglew_static opengl32 glm graphics)

add_subdirectory(graphics)
