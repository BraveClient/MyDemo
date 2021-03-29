aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs/globalData)
add_library(globalData STATIC ${DIR_LIB_SRCS})