cmake_minimum_required(VERSION 3.3)
project(lib)

# Add third-party libraries
add_subdirectory(imgui)
add_subdirectory(SDL2-2.0.7)
# add_subdirectory(lua-5.3.4)

set(SPDLOG_HEADERS "${PROJECT_SOURCE_DIR}/spdlog/include" PARENT_SCOPE)
set(CATCH_HEADERS "${PROJECT_SOURCE_DIR}/catch" PARENT_SCOPE)
