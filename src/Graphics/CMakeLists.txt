add_library(graphics STATIC window.cpp shader.cpp mesh.cpp texture.cpp)

target_include_directories(graphics PUBLIC  ${MAIN_SRC_DIR})
target_include_directories(graphics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(graphics PUBLIC glfw libglew_static opengl32 glm)