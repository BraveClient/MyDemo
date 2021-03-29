aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/drivers/Led)
add_library(Led STATIC ${DIR_LIB_SRCS})