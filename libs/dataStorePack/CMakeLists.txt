aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/libs/dataStorePack)
add_library(dataStorePack STATIC ${DIR_LIB_SRCS})
target_link_libraries(dataStorePack crc)