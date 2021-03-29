aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/autoDriver)
add_library(autoDriver STATIC ${DIR_LIB_SRCS})