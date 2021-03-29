aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/workQueue)
add_library(workQueue STATIC ${DIR_LIB_SRCS})