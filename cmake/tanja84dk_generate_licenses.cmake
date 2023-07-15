set(${PROJECT_NAME}_LICENSES_MACRO_FILE ${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}_licenses_macro.h.in)

function(tanja84dk_generate_license_begin)
    if(EXISTS "${${PROJECT_NAME}_LICENSES_MACRO_FILE}")
        file(WRITE "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "")
    endif()

    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "#ifndef TANJA84DK_DOCKERLIB_LICENCES_MACRO_H\n")
    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}" "#define TANJA84DK_DOCKERLIB_LICENCES_MACRO_H\n\n")    
endfunction(tanja84dk_generate_license_begin)





function(tanja84dk_generate_license ADDED_LIBRARY_NAME)

if(EXISTS "${${ADDED_LIBRARY_NAME}_SOURCE_DIR}/LICENSE")
    file(STRINGS ${${ADDED_LIBRARY_NAME}_SOURCE_DIR}/LICENSE TEMP_LICENSE)
    string(PREPEND TEMP_LICENSE "R\"(")
    string(APPEND TEMP_LICENSE ")\"")
    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define ${ADDED_LIBRARY_NAME}_LICENSE @${ADDED_LIBRARY_NAME}_LICENSE@\n")
    set(${ADDED_LIBRARY_NAME}_LICENSE "${TEMP_LICENSE}" PARENT_SCOPE)
else()
    message("${ADDED_LIBRARY_NAME}_LICENSE is missing\nLooked in: ${${ADDED_LIBRARY_NAME}_SOURCE_DIR}")
endif()
    
endfunction(tanja84dk_generate_license)


function(tanja84dk_generate_license_manual ADDED_LIBRARY_NAME LICENSE_PATH)

if(EXISTS "${LICENSE_PATH}")
    file(STRINGS ${LICENSE_PATH} TEMP_LICENSE)
    string(PREPEND TEMP_LICENSE "R\"(")
    string(APPEND TEMP_LICENSE ")\"")
    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define ${ADDED_LIBRARY_NAME}_LICENSE @${ADDED_LIBRARY_NAME}_LICENSE@\n")
    set(${ADDED_LIBRARY_NAME}_LICENSE "${TEMP_LICENSE}" PARENT_SCOPE)
else()
    message("${ADDED_LIBRARY_NAME}_LICENSE is missing\nLooked in ${LICENSE_PATH}")
endif()
    
endfunction(tanja84dk_generate_license_manual)



function(tanja84dk_generate_license_end)
    file(APPEND "${${PROJECT_NAME}_LICENSES_MACRO_FILE}"
    "\n#endif // TANJA84DK_DOCKERLIB_LICENCES_MACRO_H\n")
endfunction(tanja84dk_generate_license_end)



#if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
#    file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE tanja84dk_crypt_LICENSE)
#    string(PREPEND tanja84dk_crypt_LICENSE "R\"(")
#    string(APPEND tanja84dk_crypt_LICENSE ")\"")
#    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define tanja84dk_crypt_LICENSE @tanja84dk_crypt_LICENSE@\n")
#else()
#    message("tanja84dk_crypt_LICENSE is missing")
#endif()



#if(EXISTS "${cryptopp-cmake_BINARY_DIR}/cryptopp/License.txt")
#    file(STRINGS ${cryptopp-cmake_BINARY_DIR}/cryptopp/License.txt cryptopp_LICENSE)
#    string(PREPEND cryptopp_LICENSE "R\"(")
#    string(APPEND cryptopp_LICENSE ")\"")
#    file(APPEND ${${PROJECT_NAME}_LICENSES_MACRO_FILE} "#define cryptopp_LICENSE @cryptopp_LICENSE@\n")
#else()
#    message("cryptopp_LICENSE is missing")
#endif()


