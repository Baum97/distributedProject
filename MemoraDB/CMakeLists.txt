cmake_minimum_required(VERSION 3.10)

project(MemoraDB)

# Add the server sub-project
add_subdirectory(server)

# Add the lib sub-project
add_subdirectory(lib)

# Add the client sub-project
add_subdirectory(client)

# Register tests with CTest
enable_testing()

# Add the client sub-project
add_subdirectory(tests)