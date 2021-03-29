cmake_minimum_required(VERSION 3.0.0)

project(DataRecorder VERSION 0.1 LANGUAGES CXX)

add_definitions(-std=c++11)


find_package(Threads REQUIRED) 

# find_library(WIRINGPI_LIBRARIES NAMES wiringPi)

# Include headers 
include_directories(${WIRINGPI_INCLUDE_DIRS})

add_subdirectory(libs)
add_subdirectory(modules)
add_subdirectory(drivers)

aux_source_directory(./ DIR_SRCS)
add_executable(${PROJECT_NAME} ${DIR_SRCS})

# Link against libraries 
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) 
# target_link_libraries(${PROJECT_NAME} ${WIRINGPI_LIBRARIES})

# Link Modules
target_link_libraries(${PROJECT_NAME} cyclic_storage)
target_link_libraries(${PROJECT_NAME} udpReceiver)
target_link_libraries(${PROJECT_NAME} udpSender)
target_link_libraries(${PROJECT_NAME} wirteFile)
target_link_libraries(${PROJECT_NAME} logger)
target_link_libraries(${PROJECT_NAME} selfcheck)

# Link libs
target_link_libraries(${PROJECT_NAME} globalData)
target_link_libraries(${PROJECT_NAME} dataStorePack)
target_link_libraries(${PROJECT_NAME} assisant)
# target_link_libraries(${PROJECT_NAME} AP_Math)







# set(EXECUTABLE_OUTPUT_PATH ${PROJ})




#向工程添加多个特定的头文件搜索路径
#include_directories([AFTER|BEFORC] [SYSTEM] dir1 dir2 ...)
# include_directories(./include) 

# add_subdirectory(lib)
# add_subdirectory(modules)

# add_executable(${PROJECT_NAME}
#     main.cpp bd.cpp
# )



