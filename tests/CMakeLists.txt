cmake_minimum_required(VERSION 3.3)

project(tests C CXX)

include_directories(
  ${GLFW_HEADERS}
  ${CATCH_HEADERS}
  ${SDL2_HEADERS}
)

# Runtime executable
add_executable(tests main.cpp rendering.cpp)
# Linking against static libraries
target_link_libraries(tests SDL2)
set_target_properties(tests PROPERTIES OUTPUT_NAME "run-tests")
