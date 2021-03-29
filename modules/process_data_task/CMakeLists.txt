aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/process_data_task)
add_library(process_data_task STATIC ${DIR_LIB_SRCS})