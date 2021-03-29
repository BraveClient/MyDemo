aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/logger)
add_library(logger STATIC ${DIR_LIB_SRCS})