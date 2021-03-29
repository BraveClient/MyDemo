aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/udpReceiver)
add_library(udpReceiver STATIC ${DIR_LIB_SRCS})