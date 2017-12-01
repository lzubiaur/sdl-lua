cmake_minimum_required(VERSION 3.3)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
  ${PROJECT_BINARY_DIR}/src
  ${SDL2_HEADERS}
)

add_library(engine STATIC Engine.cpp)
target_link_libraries(engine SDL2 gl3w imgui Lua sdlimg)
# target_include_directories(engine PUBLIC ${PROJECT_SOURCE_DIR}/src)

# Runtime executable
add_executable(rt main.cpp)
target_link_libraries(rt engine)
set_target_properties(rt PROPERTIES OUTPUT_NAME ${RUNTIME_NAME})
