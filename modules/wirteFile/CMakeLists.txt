aux_source_directory(. DIR_LIB_SRCS)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/modules/wirteFile)
add_library(wirteFile STATIC ${DIR_LIB_SRCS})
target_link_libraries(wirteFile cyclic_storage dataStorePack)