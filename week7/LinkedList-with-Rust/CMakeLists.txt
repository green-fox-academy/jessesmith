cmake_minimum_required(VERSION 3.14)
project(LinkedList C)
#set(PROJECT_NAME LinkedList)

set(CMAKE_C_STANDARD 99)

#add_executable(LinkedList main.c)

# Change this to the name of the directory that contains your code
set(PROJECT_LIB_NAME app_lib)

# Change this to the name of the directory that contains your tests
set(PROJECT_TESTS_NAME app_tests)

# Change this to the path where you extracted the Google Test files to
set(PATH_TO_GOOGLETEST "/Users/jessesmith/utilities/googletest")

# Change this to your project name (optional)
#set(PROJECT_NAME gtest_c_example_app)



project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_C_STANDARD 99)

# The next line creates an executable file from main.cpp with the same name as your project
add_executable(${PROJECT_NAME} main.c)

# This block includes the subdirectories containing your code and tests
add_subdirectory(${PROJECT_LIB_NAME})
add_subdirectory(${PROJECT_TESTS_NAME})



# This line links your code to the main executable
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB_NAME})

link_directories(/Users/jessesmith/Proj/greenfox/jessesmith/week7/LinkedList-with-Rust/linkedlist-ffi/target/release)
target_link_libraries(${PROJECT_NAME} rust_linked_list)
#add_library(RUSTLL SHARED IMPORTED GLOBAL)
#set_target_properties(RUSTLL PROPERTIES IMPORTED_LOCATION linkedlist-ffi/target/release/librust_linked_list.dylib )
#target_link_libraries(${PROJECT_NAME} RUSTLL)