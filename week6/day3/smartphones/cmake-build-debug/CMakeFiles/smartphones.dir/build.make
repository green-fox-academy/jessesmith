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
CMAKE_SOURCE_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/smartphones.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/smartphones.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/smartphones.dir/flags.make

CMakeFiles/smartphones.dir/main.c.o: CMakeFiles/smartphones.dir/flags.make
CMakeFiles/smartphones.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/smartphones.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/smartphones.dir/main.c.o   -c /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/main.c

CMakeFiles/smartphones.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/smartphones.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/main.c > CMakeFiles/smartphones.dir/main.c.i

CMakeFiles/smartphones.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/smartphones.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/main.c -o CMakeFiles/smartphones.dir/main.c.s

# Object files for target smartphones
smartphones_OBJECTS = \
"CMakeFiles/smartphones.dir/main.c.o"

# External object files for target smartphones
smartphones_EXTERNAL_OBJECTS =

smartphones: CMakeFiles/smartphones.dir/main.c.o
smartphones: CMakeFiles/smartphones.dir/build.make
smartphones: CMakeFiles/smartphones.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable smartphones"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/smartphones.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/smartphones.dir/build: smartphones

.PHONY : CMakeFiles/smartphones.dir/build

CMakeFiles/smartphones.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/smartphones.dir/cmake_clean.cmake
.PHONY : CMakeFiles/smartphones.dir/clean

CMakeFiles/smartphones.dir/depend:
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug /Users/jessesmith/Proj/greenfox/jessesmith/week6/day3/smartphones/cmake-build-debug/CMakeFiles/smartphones.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/smartphones.dir/depend

