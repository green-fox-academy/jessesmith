# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug

# Include any dependencies generated for this target.
include app_tests/CMakeFiles/app_tests.dir/depend.make

# Include the progress variables for this target.
include app_tests/CMakeFiles/app_tests.dir/progress.make

# Include the compile flags for this target's objects.
include app_tests/CMakeFiles/app_tests.dir/flags.make

app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.o: app_tests/CMakeFiles/app_tests.dir/flags.make
app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.o: ../app_tests/linked_list_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.o"
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/app_tests.dir/linked_list_tests.cpp.o -c /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/app_tests/linked_list_tests.cpp

app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/app_tests.dir/linked_list_tests.cpp.i"
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/app_tests/linked_list_tests.cpp > CMakeFiles/app_tests.dir/linked_list_tests.cpp.i

app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/app_tests.dir/linked_list_tests.cpp.s"
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/app_tests/linked_list_tests.cpp -o CMakeFiles/app_tests.dir/linked_list_tests.cpp.s

# Object files for target app_tests
app_tests_OBJECTS = \
"CMakeFiles/app_tests.dir/linked_list_tests.cpp.o"

# External object files for target app_tests
app_tests_EXTERNAL_OBJECTS =

app_tests/app_tests: app_tests/CMakeFiles/app_tests.dir/linked_list_tests.cpp.o
app_tests/app_tests: app_tests/CMakeFiles/app_tests.dir/build.make
app_tests/app_tests: lib/libgtestd.a
app_tests/app_tests: lib/libgtest_maind.a
app_tests/app_tests: app_lib/libapp_lib.a
app_tests/app_tests: lib/libgtestd.a
app_tests/app_tests: app_tests/CMakeFiles/app_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable app_tests"
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app_tests/CMakeFiles/app_tests.dir/build: app_tests/app_tests

.PHONY : app_tests/CMakeFiles/app_tests.dir/build

app_tests/CMakeFiles/app_tests.dir/clean:
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests && $(CMAKE_COMMAND) -P CMakeFiles/app_tests.dir/cmake_clean.cmake
.PHONY : app_tests/CMakeFiles/app_tests.dir/clean

app_tests/CMakeFiles/app_tests.dir/depend:
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/app_tests /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests /Users/jessesmith/Proj/greenfox/jessesmith/week6/day4/LinkedList/cmake-build-debug/app_tests/CMakeFiles/app_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app_tests/CMakeFiles/app_tests.dir/depend

