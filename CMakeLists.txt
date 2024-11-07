cmake_minimum_required(VERSION 3.16)
project(cas)
set(CMAKE_CXX_STANDARD 17)

include(libcas/CMakeLists.txt)
include(libcas-tst/CMakeLists.txt)
include(cas/CMakeLists.txt)

add_library(libcas ${LIBCAS_SOURCES})
target_include_directories(libcas PRIVATE "libcas")

add_executable(libcas-tst ${LIBCAS_TST_SOURCES})
target_include_directories(libcas-tst PRIVATE "libcas")
target_link_libraries(libcas-tst PRIVATE gtest gtest_main libcas)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtkmm-4.0)

add_executable(cas ${CAS_SOURCES})
target_link_libraries(cas PkgConfig::GTK4 "libcas")
target_include_directories(cas PRIVATE "libcas")

enable_testing()
add_test(NAME libcas-tst COMMAND libcas-tst)
