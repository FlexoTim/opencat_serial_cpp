cmake_minimum_required(VERSION 3.0.2)
project(opencat_serial)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-std=c++11)

option(CATKIN_ENABLE "Enable using the Catkin make extension to cmake (ie for ROS)" ON)

# include serial lib
add_subdirectory(serial)

# declare lib
add_library(
  ${PROJECT_NAME}
  src/${PROJECT_NAME}.cpp
)

# include and linking
target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  include/
)
target_link_libraries(${PROJECT_NAME} PRIVATE serial)

if(${CATKIN_ENABLE})
  find_package(
    catkin REQUIRED COMPONENTS
    roscpp
  )

  catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    CATKIN_DEPENDS roscpp
  )

  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${catkin_INCLUDE_DIRS}
  )

  # install so that can be used by other ros packages
  install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION}
  )

  ## Mark cpp header files for installation
  install(
    DIRECTORY include/${PROJECT_NAME}/
    DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  )
endif()
