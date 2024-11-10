find_package(Doxygen)
if(Doxygen_FOUND)
    configure_file("${CMAKE_CURRENT_LIST_DIR}/Doxyfile" "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")

    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
else()
    message(STATUS "Doxygen not found, not building docs")
endif()
