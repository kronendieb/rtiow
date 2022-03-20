
add_library(window STATIC window.cpp)

target_include_directories(window PUBLIC  ${MAIN_SRC_DIR})
target_include_directories(window PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(window PUBLIC glfw opengl32 glm)