set(MAIN_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp app.cpp ../ext/stbi/stb_image.h)

target_include_directories(${PROJECT_NAME} 
    PUBLIC Graphics 
    PRIVATE Raytracing
    PUBLIC ext/glfw/include
    PUBLIC ext/glew/include
    PUBLIC ext/stbi
    PUBLIC ext/glm)

target_link_directories(${PROJECT_NAME} 
    PRIVATE Graphics
    PRIVATE Raytracing
    PRIVATE ext/glfw/src
    PRIVATE ext/glew/lib
    PRIVATE ext/glm)

target_link_libraries(${PROJECT_NAME} glfw libglew_static opengl32 glm graphics raytracing)

add_subdirectory(graphics)
add_subdirectory(raytracing)
