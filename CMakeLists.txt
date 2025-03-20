cmake_minimum_required(VERSION 3.16)
project(JSONPlugin VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

# Find Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Set paths for CubeGUI and CubeLib
set(CUBEGUI_CONFIG "/Users/nandhish/Studies/CubeGUI/cubeGUI/bin/cubegui-config")
set(CUBELIB_CONFIG "/Users/nandhish/Studies/CubeGUI/cubeLib/bin/cubelib-config")

# Get includes and libs using string(STRIP) to handle whitespace properly
execute_process(COMMAND ${CUBEGUI_CONFIG} --include OUTPUT_VARIABLE CUBEGUI_INCLUDE OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CUBELIB_CONFIG} --include OUTPUT_VARIABLE CUBELIB_INCLUDE OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CUBEGUI_CONFIG} --ldflags OUTPUT_VARIABLE CUBEGUI_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CUBEGUI_CONFIG} --libs OUTPUT_VARIABLE CUBEGUI_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CUBELIB_CONFIG} --ldflags OUTPUT_VARIABLE CUBELIB_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${CUBELIB_CONFIG} --libs OUTPUT_VARIABLE CUBELIB_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

# Process flags to avoid whitespace issues
string(REPLACE " " ";" CUBEGUI_LDFLAGS_LIST "${CUBEGUI_LDFLAGS}")
string(REPLACE " " ";" CUBEGUI_LIBS_LIST "${CUBEGUI_LIBS}")
string(REPLACE " " ";" CUBELIB_LDFLAGS_LIST "${CUBELIB_LDFLAGS}")
string(REPLACE " " ";" CUBELIB_LIBS_LIST "${CUBELIB_LIBS}")

# Add includes
include_directories(${CUBEGUI_INCLUDE} ${CUBELIB_INCLUDE})

# Create the plugin
add_library(JSONPlugin MODULE JsonPlugin.h JsonPlugin.cpp)
set_target_properties(JSONPlugin PROPERTIES
    PREFIX ""
    OUTPUT_NAME "json_plugin"
)
# Link libraries
target_link_libraries(JSONPlugin PRIVATE
    Qt6::Widgets
    ${CUBEGUI_LDFLAGS_LIST}
    ${CUBEGUI_LIBS_LIST}
    ${CUBELIB_LDFLAGS_LIST}
    ${CUBELIB_LIBS_LIST}
)

# Install
install(TARGETS JSONPlugin LIBRARY DESTINATION plugins)
