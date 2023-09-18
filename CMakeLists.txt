cmake_minimum_required(VERSION 3.0.0)
project(main)

find_library(SDL2_LIB SDL2)
find_library(SDL2_IMAGE_LIB SDL2_image)
find_library(freetype freetype)
find_library(stb stb)
find_package(OpenGL REQUIRED)
add_definitions(-DHD=1)
add_executable(main src/main.cpp)

file(GLOB_RECURSE my_libs
"${CMAKE_CURRENT_SOURCE_DIR}/src/libs/*"
"${CMAKE_CURRENT_SOURCE_DIR}/submods/bgfx/include/*"
"${CMAKE_CURRENT_SOURCE_DIR}/submods/bx/include/*"
# "${CMAKE_CURRENT_SOURCE_DIR}/submods/tinyobjloader/tiny_obj_loader.h"
)
add_library(my_libs ${my_libs})
target_include_directories(my_libs PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/src/libs/
${CMAKE_CURRENT_SOURCE_DIR}/submods/bgfx/include/
${CMAKE_CURRENT_SOURCE_DIR}/submods/bx/include/
${CMAKE_CURRENT_SOURCE_DIR}/submods/bimg/include/
${CMAKE_CURRENT_SOURCE_DIR}/submods/imgui/
${CMAKE_CURRENT_SOURCE_DIR}/submods/bgfx/examples/common/
)

set(BGFX_DIR "${CMAKE_CURRENT_SOURCE_DIR}/submods/bgfx")

set(SHADERC_EXECUTABLE "${CMAKE_CURRENT_SOURCE_DIR}/src/libs/shaders/shadercRelease")

# Check if the executable exists
if(NOT EXISTS ${SHADERC_EXECUTABLE})
    message(FATAL_ERROR "shadercRelease executable not found at ${SHADERC_EXECUTABLE}")
endif()

# make a shaders directory in build source if it doesnt exist already
if(NOT EXISTS ${CMAKE_BINARY_DIR}/shaders)
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
endif()

file(GLOB SHADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/shaders/*.sc)

foreach(SHADER ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER} NAME)
    get_filename_component(FILE_NAME_WE ${SHADER} NAME_WE)
    if(${FILE_NAME} MATCHES "v_.*")
        set(TYPE "vertex")
    elseif(${FILE_NAME} MATCHES "f_.*")
        set(TYPE "fragment")
    elseif(${FILE_NAME} MATCHES "varying.*")
        continue()
    else()
        message(FATAL_ERROR "Unknown shader type for ${FILE_NAME}")
    endif()
    message(STATUS "Compiling ${FILE_NAME} as ${TYPE}")
    execute_process(
        COMMAND ${SHADERC_EXECUTABLE}
        ARGS -f ${SHADER} -o shaders/${FILE_NAME_WE}.bin --platform linux --type ${TYPE} --verbose -i ${BGFX_DIR}/src
        RESULT_VARIABLE result
    )
    if(NOT ${result} EQUAL 0)
        message(FATAL_ERROR "shaderc failed to compile ${FILE_NAME}")
    endif()
endforeach()


# execute_process(
#     COMMAND ${SHADERC_EXECUTABLE}
#     ARGS -f ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/shaders/v_basic_mat.sc -o shaders/v_basic_mat.bin --platform linux --type vertex --verbose -i ${BGFX_DIR}/src
#     RESULT_VARIABLE vresult
# )
# if(NOT ${vresult} EQUAL 0)
#     message(FATAL_ERROR "shaderc failed to compile v_simple.sc")
# endif()

# execute_process(
#     COMMAND ${SHADERC_EXECUTABLE}
#     ARGS -f ${CMAKE_CURRENT_SOURCE_DIR}/src/libs/shaders/f_basic_mat.sc -o shaders/f_basic_mat.bin --platform linux --type fragment --verbose -i ${BGFX_DIR}/src
#     RESULT_VARIABLE fresult
# )
# if(NOT ${fresult} EQUAL 0)
#     message(FATAL_ERROR "shaderc failed to compile f_simple.sc")
# endif()

target_include_directories(main PUBLIC 
submods/bgfx/include 
submods/bx/include
submods/bimg/include
submods/bgfx/examples/common
submods/bgfx/3rdparty
)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/submods/RmlUi/Include)
# add_subdirectory(submods/RmlUi)

SET(BGFX_SHARED_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/submods/bgfx/.build/linux64_gcc/bin)
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DBX_CONFIG_DEBUG=0")
target_link_libraries(main 
PRIVATE
my_libs
# RmlCore
# RmlDebugger
stb
freetype
${OPENGL_gl_LIBRARY} 
${SDL2_LIB} 
${SDL2_IMAGE_LIB}
${BGFX_SHARED_LIB_DIR}/libbgfx-shared-libRelease.so
)