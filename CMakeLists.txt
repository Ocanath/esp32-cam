cmake_minimum_required(VERSION 3.16)

# Local components (vendor_libs) plus the forked camera-stream component.
# NOTE: the component name is the directory name: "xiao-esp32-camera-stream".
set(EXTRA_COMPONENT_DIRS
    "${CMAKE_CURRENT_LIST_DIR}/components"
    "${CMAKE_CURRENT_LIST_DIR}/external/xiao-esp32-camera-stream"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(robot_cam)
