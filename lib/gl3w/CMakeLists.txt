cmake_minimum_required(VERSION 3.1.3 FATAL_ERROR)

project(gl3w)

set(CMAKE_VERBOSE_MAKEFILE false)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # -fPIC

set(SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)

set(HEADER_FILES
	"${HEADER_DIR}/GL/gl3w.h"
	"${HEADER_DIR}/GL/glcorearb.h"
)

set(SOURCE_FILES
	"${SOURCE_DIR}/gl3w.c"
)

# add and depend on OpenGL
find_package(OpenGL REQUIRED)
set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR})
set(EXTERNAL_LIBRARIES ${EXTERNAL_LIBRARIES} ${OPENGL_LIBRARIES})

# add command to create the header and source files
add_custom_command(
	OUTPUT
		"${SOURCE_DIR}/gl3w.c"
		"${HEADER_DIR}/GL/gl3w.h"
		"${HEADER_DIR}/GL/glcorearb.h"
	COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/gl3w_gen.py
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gl3w_gen.py
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# add pseudo target that depends on the generated files
add_custom_target(
	gl3w_gen ALL
	DEPENDS
		"${SOURCE_DIR}/gl3w.c"
		"${HEADER_DIR}/GL/gl3w.h"
		"${HEADER_DIR}/GL/glcorearb.h"
)

# create gl3w target
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# make gl3w target depend on the generator target
add_dependencies(${PROJECT_NAME} gl3w_gen)

# let remote project know about source and header files
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNAL_INCLUDE_DIRS})
# let remote project know which libraries need to be linked
target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBRARIES} ${CMAKE_DL_LIBS})
