aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs/cyclic_storage)
add_library(cyclic_storage STATIC ${DIR_LIB_SRCS})