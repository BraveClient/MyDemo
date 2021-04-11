cmake_minimum_required(VERSION 3.0.0)

project(MYDEMO VERSION 0.1 LANGUAGES CXX)

add_definitions(-std=c++11)

include_directories(./include)
find_package(Threads REQUIRED) 


# find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

# Include headers 
include_directories(${WIRINGPI_INCLUDE_DIRS})



aux_source_directory(./ DIR_SRCS)

add_executable(${PROJECT_NAME}
    main.cpp
  )


# Link against libraries 
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) 
# target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES})





