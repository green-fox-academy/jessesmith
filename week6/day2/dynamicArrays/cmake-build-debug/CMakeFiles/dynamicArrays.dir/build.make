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
CMAKE_SOURCE_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/dynamicArrays.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/dynamicArrays.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/dynamicArrays.dir/flags.make

CMakeFiles/dynamicArrays.dir/main.c.o: CMakeFiles/dynamicArrays.dir/flags.make
CMakeFiles/dynamicArrays.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/dynamicArrays.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/dynamicArrays.dir/main.c.o   -c /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/main.c

CMakeFiles/dynamicArrays.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/dynamicArrays.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/main.c > CMakeFiles/dynamicArrays.dir/main.c.i

CMakeFiles/dynamicArrays.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/dynamicArrays.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/main.c -o CMakeFiles/dynamicArrays.dir/main.c.s

# Object files for target dynamicArrays
dynamicArrays_OBJECTS = \
"CMakeFiles/dynamicArrays.dir/main.c.o"

# External object files for target dynamicArrays
dynamicArrays_EXTERNAL_OBJECTS =

dynamicArrays: CMakeFiles/dynamicArrays.dir/main.c.o
dynamicArrays: CMakeFiles/dynamicArrays.dir/build.make
dynamicArrays: CMakeFiles/dynamicArrays.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable dynamicArrays"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dynamicArrays.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/dynamicArrays.dir/build: dynamicArrays

.PHONY : CMakeFiles/dynamicArrays.dir/build

CMakeFiles/dynamicArrays.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/dynamicArrays.dir/cmake_clean.cmake
.PHONY : CMakeFiles/dynamicArrays.dir/clean

CMakeFiles/dynamicArrays.dir/depend:
	cd /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug /Users/jessesmith/Proj/greenfox/jessesmith/week6/dynamicArrays/cmake-build-debug/CMakeFiles/dynamicArrays.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/dynamicArrays.dir/depend

