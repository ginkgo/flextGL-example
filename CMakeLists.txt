
cmake_minimum_required(VERSION 2.8)
project(example)

option(TARGET_GLES "Target OpenGL ES 2.0 instead of desktop GL" OFF)

find_package(PythonInterp REQUIRED)
find_package(OpenGL REQUIRED)
find_library(GLFW_LIBRARIES glfw)

if (WIN32)
	set(PYTHON_EXECUTABLE "C:/python32/python.exe")
	include_directories("${PROJECT_SOURCE_DIR}/glfw/include")
	
	find_library(GLFW_LIBRARIES glfw3.lib PATHS glfw/lib/win32)
endif()

include_directories("${PROJECT_BINARY_DIR}/generated")

if(NOT TARGET_GLES)
    set(profile profile.txt)
    set(template glfw3)
    set(shader_vert example.vert)
    set(shader_frag example.frag)
else()
    set(profile profile-es.txt)
    set(template glfw3-es)
    set(shader_vert example-es.vert)
    set(shader_frag example-es.frag)
endif()

add_custom_command(OUTPUT "${PROJECT_BINARY_DIR}/generated/flextGL.h" "${PROJECT_BINARY_DIR}/generated/flextGL.c"
                   COMMAND ${PYTHON_EXECUTABLE} "${PROJECT_SOURCE_DIR}/flextGL/flextGLgen.py" -Dgenerated -T${template} ${PROJECT_SOURCE_DIR}/${profile}
                   DEPENDS ${PROJECT_SOURCE_DIR}/${profile}
                           ${PROJECT_SOURCE_DIR}/flextGL/flextGLgen.py
                           ${PROJECT_SOURCE_DIR}/flextGL/flext.py
                           ${PROJECT_SOURCE_DIR}/flextGL/templates/${template}/flextGL.h.template
                           ${PROJECT_SOURCE_DIR}/flextGL/templates/${template}/flextGL.c.template)

set(SOURCE_FILES example.cpp mesh.cpp utility.cpp)
set(HEADER_FILES common.hpp mesh.hpp utility.hpp)
set(SHADERS example.frag example.vert)

add_executable(example ${SOURCE_FILES} ${HEADER_FILES} ${SHADERS} ${profile} generated/flextGL.c)
target_link_libraries(example ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES} ${GLEW_LIBRARIES})
if(TARGET_GLES)
    set_target_properties(example PROPERTIES COMPILE_DEFINITIONS "TARGET_GLES")
endif()

add_custom_command(TARGET example COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "${PROJECT_SOURCE_DIR}/${shader_frag}" "${PROJECT_BINARY_DIR}")
add_custom_command(TARGET example COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   "${PROJECT_SOURCE_DIR}/${shader_vert}" "${PROJECT_BINARY_DIR}")
