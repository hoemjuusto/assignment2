# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /snap/clion/92/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/92/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/juuso/CLionProjects/assignment2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/juuso/CLionProjects/assignment2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/assignment2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/assignment2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/assignment2.dir/flags.make

CMakeFiles/assignment2.dir/main.c.o: CMakeFiles/assignment2.dir/flags.make
CMakeFiles/assignment2.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/juuso/CLionProjects/assignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/assignment2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/assignment2.dir/main.c.o   -c /home/juuso/CLionProjects/assignment2/main.c

CMakeFiles/assignment2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/assignment2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/juuso/CLionProjects/assignment2/main.c > CMakeFiles/assignment2.dir/main.c.i

CMakeFiles/assignment2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/assignment2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/juuso/CLionProjects/assignment2/main.c -o CMakeFiles/assignment2.dir/main.c.s

# Object files for target assignment2
assignment2_OBJECTS = \
"CMakeFiles/assignment2.dir/main.c.o"

# External object files for target assignment2
assignment2_EXTERNAL_OBJECTS =

assignment2: CMakeFiles/assignment2.dir/main.c.o
assignment2: CMakeFiles/assignment2.dir/build.make
assignment2: CMakeFiles/assignment2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/juuso/CLionProjects/assignment2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable assignment2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/assignment2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/assignment2.dir/build: assignment2

.PHONY : CMakeFiles/assignment2.dir/build

CMakeFiles/assignment2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/assignment2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/assignment2.dir/clean

CMakeFiles/assignment2.dir/depend:
	cd /home/juuso/CLionProjects/assignment2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/juuso/CLionProjects/assignment2 /home/juuso/CLionProjects/assignment2 /home/juuso/CLionProjects/assignment2/cmake-build-debug /home/juuso/CLionProjects/assignment2/cmake-build-debug /home/juuso/CLionProjects/assignment2/cmake-build-debug/CMakeFiles/assignment2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/assignment2.dir/depend

