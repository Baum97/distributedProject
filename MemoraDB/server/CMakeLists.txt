set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_library(memora_server_lib STATIC memora_server.c)
target_include_directories(memora_server_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(memora_server_lib ${CHECK_LIBRARIES} Threads::Threads)

add_executable(memora_server main.c)
target_link_libraries(memora_server memora_server_lib memora rt)
