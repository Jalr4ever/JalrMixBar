# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/jalr/文档/Clion/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/jalr/文档/Clion/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jalr/CLionProjects/5th-Lab

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jalr/CLionProjects/5th-Lab/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/5thPart-3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5thPart-3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5thPart-3.dir/flags.make

CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o: CMakeFiles/5thPart-3.dir/flags.make
CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o: ../5thBin/5th-part3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jalr/CLionProjects/5th-Lab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o   -c /home/jalr/CLionProjects/5th-Lab/5thBin/5th-part3.c

CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jalr/CLionProjects/5th-Lab/5thBin/5th-part3.c > CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.i

CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jalr/CLionProjects/5th-Lab/5thBin/5th-part3.c -o CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.s

# Object files for target 5thPart-3
5thPart__3_OBJECTS = \
"CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o"

# External object files for target 5thPart-3
5thPart__3_EXTERNAL_OBJECTS =

5thPart-3: CMakeFiles/5thPart-3.dir/5thBin/5th-part3.c.o
5thPart-3: CMakeFiles/5thPart-3.dir/build.make
5thPart-3: CMakeFiles/5thPart-3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jalr/CLionProjects/5th-Lab/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 5thPart-3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5thPart-3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5thPart-3.dir/build: 5thPart-3

.PHONY : CMakeFiles/5thPart-3.dir/build

CMakeFiles/5thPart-3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5thPart-3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5thPart-3.dir/clean

CMakeFiles/5thPart-3.dir/depend:
	cd /home/jalr/CLionProjects/5th-Lab/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jalr/CLionProjects/5th-Lab /home/jalr/CLionProjects/5th-Lab /home/jalr/CLionProjects/5th-Lab/cmake-build-debug /home/jalr/CLionProjects/5th-Lab/cmake-build-debug /home/jalr/CLionProjects/5th-Lab/cmake-build-debug/CMakeFiles/5thPart-3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5thPart-3.dir/depend

