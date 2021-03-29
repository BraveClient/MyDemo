MACRO(getSubDirList result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

getSubDirList(SUBDIRS ${CMAKE_CURRENT_LIST_DIR})

message("~~~~~~~~~~~~~~~lib list~~~~~~~~~~~~~~~~~~~~")
FOREACH(subdir ${SUBDIRS})
    message(${subdir})
    add_subdirectory(${subdir})
ENDFOREACH()




# add_subdirectory(cyclic_storage)
# add_subDirectory(dataStore)
# add_subdirectory(crc)
# add_subdirectory(globalData)