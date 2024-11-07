list(APPEND CAS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/button.cpp
)

include("${CMAKE_CURRENT_LIST_DIR}/modes/CMakeLists.txt")
