cmake_minimum_required(VERSION 2.8.3)

project(auv_sonar)

add_definitions("-std=c++14")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)



 generate_messages(
   DEPENDENCIES
   std_msgs
 )



catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  include/
)

add_library(auv_sonar
  src/Multilateration.cpp
)

target_link_libraries(auv_sonar ${catkin_LIBRARIES})

add_dependencies(auv_sonar
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

add_executable(auv_sonar_cont src/main.cpp)

target_link_libraries(auv_sonar_cont ${catkin_LIBRARIES} auv_sonar)
add_dependencies(auv_sonar_cont
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
