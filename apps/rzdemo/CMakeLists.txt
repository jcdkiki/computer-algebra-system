add_executable(rzdemo main.cpp)
target_link_libraries(rzdemo rznumbers)
target_compile_features(rzdemo PRIVATE cxx_std_17)

target_include_directories(rzdemo PRIVATE ${PROJECT_SOURCE_DIR}/3rd/args/include)
