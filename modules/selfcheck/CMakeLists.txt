aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/selfcheck)
add_library(selfcheck STATIC ${DIR_LIB_SRCS})