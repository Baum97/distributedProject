include_directories(${PROJECT_SOURCE_DIR}/lib)
add_executable(memora_client main.c)
target_link_libraries(memora_client memora pthread)