set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

# Find Check library
find_package(Check REQUIRED)
include_directories(${CHECK_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/server)


# Set the build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set the appropriate compiler flags for debugging
set(CMAKE_C_FLAGS_DEBUG "-g -O0")

add_executable(memora_server_tests memora_server_test.c)
target_link_libraries(memora_server_tests memora_server_lib ${CHECK_LIBRARIES} pthread m rt subunit)

add_executable(memora_lib_tests memora_lib_test.c)
target_link_libraries(memora_lib_tests memora ${CHECK_LIBRARIES} pthread m rt subunit)

add_executable(memora_client_tests memora_client_test.c)
target_link_libraries(memora_client_tests ${CHECK_LIBRARIES} pthread m rt subunit)

add_test(NAME memora_server_tests COMMAND memora_server_tests)
add_test(NAME memora_lib_tests COMMAND memora_lib_tests)
add_test(NAME memora_client_tests COMMAND memora_client_tests)