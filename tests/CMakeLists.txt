cmake_minimum_required(VERSION 3.3)

project(tests C CXX)

include_directories(
  ${GLFW_HEADERS}
  ${CATCH_HEADERS}
  ${SDL2_HEADERS}
)

# Runtime executable
add_executable(tests main.cpp rendering.cpp scripting.cpp)
add_dependencies(tests SDL2 liblua)

if(BUILD_OSX)
     # Must defined pagezero_size and image_base or LuaJIT will crash on MacOSX 64bits. See luajit.org/install.html for flags
    set_target_properties(tests PROPERTIES LINK_FLAGS "-pagezero_size 10000 -image_base 100000000")
endif()

# Linking against static libraries
target_link_libraries(tests SDL2 Lua)
set_target_properties(tests PROPERTIES OUTPUT_NAME "run-tests")

# Copy lua scripts to the binary folder
file(GLOB RESOURCES RELATIVE "${PROJECT_SOURCE_DIR}" "*.lua")
file(COPY ${RESOURCES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
