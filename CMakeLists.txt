cmake_minimum_required(VERSION 3.5)
project(auto)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()
# find dependencies
find_package(ament_cmake REQUIRED)
find_package(ament_cmake_ros REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclpy REQUIRED)
include_directories("include/auto")
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

#Node
add_executable(compute src/Compute.c src/compute_node.cpp)
ament_target_dependencies(compute "rclcpp" "std_msgs")


#Launch
#install(DIRECTORY
#        launch
#        DESTINATION share/${PROJECT_NAME}/)

#Directory
#target_include_directories(sense PUBLIC
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#  $<INSTALL_INTERFACE:include>)
#target_link_libraries(sense m)
#install(TARGETS sense
#  EXPORT export_${PROJECT_NAME}
#  DESTINATION lib/${PROJECT_NAME})

install(TARGETS compute
  DESTINATION lib/${PROJECT_NAME})




ament_export_include_directories(
  include
)

ament_package()
