find_package(PkgConfig)

if(NOT PkgConfig_FOUND)
    message("PkgConfig not found. Can't build rzcas")
    return()
endif()

pkg_check_modules(GTK IMPORTED_TARGET gtkmm-4.0)

if(NOT GTK_FOUND)
    message("GTK not found. Can't build rzcas")
    return()
endif()

add_executable(rzcas)
target_link_libraries(rzcas PkgConfig::GTK rznumbers)

target_sources(rzcas PRIVATE main.cpp window.cpp button.cpp lexer.cpp parser.cpp common_mode.cpp)
add_subdirectory(modes)
add_subdirectory(parsers)

