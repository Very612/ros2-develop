cmake_minimum_required(VERSION 3.8)
project(packname)  # 这里！！写Packname

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 寻找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# 发布节点 talker
add_executable(talker src/publisher.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

# 订阅节点 listener
add_executable(listener src/subscriber.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

# 安装！！这一段不能丢，不然ros2 run找不到程序
install(TARGETS
  talker
  listener
  DESTINATION lib/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
