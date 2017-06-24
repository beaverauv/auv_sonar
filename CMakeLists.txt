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

 add_library(alglib
   src/alglib/alglibinternal.cpp
   src/alglib/alglibmisc.cpp
   src/alglib/ap.cpp
   src/alglib/dataanalysis.cpp
   src/alglib/diffequations.cpp
   src/alglib/fasttransforms.cpp
   src/alglib/integration.cpp
   src/alglib/interpolation.cpp
   src/alglib/linalg.cpp
   src/alglib/optimization.cpp
   src/alglib/solvers.cpp
   src/alglib/specialfunctions.cpp
   src/alglib/statistics.cpp
 )
 target_include_directories(alglib PUBLIC include/alglib)


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

target_link_libraries(auv_sonar_cont ${catkin_LIBRARIES} auv_sonar alglib)
add_dependencies(auv_sonar_cont
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
