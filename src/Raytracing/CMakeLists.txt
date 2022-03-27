add_library(raytracing STATIC ray.cpp raytracing.cpp sphere.cpp hittable.cpp camera.cpp)

target_include_directories(raytracing PUBLIC  ${MAIN_SRC_DIR})
target_include_directories(raytracing PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(raytracing PUBLIC glfw libglew_static opengl32 glm graphics)