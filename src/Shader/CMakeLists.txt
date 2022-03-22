add_library(shader STATIC shader.cpp)

target_include_directories(shader PUBLIC  ${MAIN_SRC_DIR})
target_include_directories(shader PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(shader PUBLIC glfw libglew_static opengl32 glm)