cmake_minimum_required(VERSION 3.3)
project(lib)

# Add third-party libraries
add_subdirectory(gl3w)
add_subdirectory(imgui)
add_subdirectory(SDL2-2.0.7)
# add_subdirectory(SDL2_image-2.0.2)
add_subdirectory(LuaJIT-2.0.5)

set(SPDLOG_HEADERS "${PROJECT_SOURCE_DIR}/spdlog/include" PARENT_SCOPE)
set(CATCH_HEADERS "${PROJECT_SOURCE_DIR}/catch" PARENT_SCOPE)
set(SDL2_HEADERS "${PROJECT_SOURCE_DIR}/SDL2-2.0.7/include" PARENT_SCOPE)
