cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(libimgui C CXX)

include_directories(
    ../SDL2-2.0.7/include
    ../gl3w/include
)

set(IMGUI_SRC
  imgui.cpp
  imgui_demo.cpp
  imgui_draw.cpp
  examples/sdl_opengl3_example/imgui_impl_sdl_gl3.cpp
)

add_library(imgui STATIC ${IMGUI_SRC})
target_link_libraries(imgui SDL2)

target_include_directories(imgui PUBLIC
  ${PROJECT_SOURCE_DIR}
  "${PROJECT_SOURCE_DIR}/examples/sdl_opengl3_example"
)
