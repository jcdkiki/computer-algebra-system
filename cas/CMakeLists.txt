list(APPEND CAS_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/button.cpp
    ${CMAKE_CURRENT_LIST_DIR}/lexer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/common_mode.cpp
)

include("${CMAKE_CURRENT_LIST_DIR}/modes/CMakeLists.txt")
include("${CMAKE_CURRENT_LIST_DIR}/parsers/CMakeLists.txt")
