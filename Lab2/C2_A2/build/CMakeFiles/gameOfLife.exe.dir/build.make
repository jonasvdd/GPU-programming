# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build"

# Include any dependencies generated for this target.
include CMakeFiles/gameOfLife.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gameOfLife.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gameOfLife.exe.dir/flags.make

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o: CMakeFiles/gameOfLife.exe.dir/flags.make
CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o: ../gameOfLife.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/gameOfLife.cpp"

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/gameOfLife.cpp" > CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.i

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/gameOfLife.cpp" -o CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.s

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.requires:

.PHONY : CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.requires

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.provides: CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.requires
	$(MAKE) -f CMakeFiles/gameOfLife.exe.dir/build.make CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.provides.build
.PHONY : CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.provides

CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.provides.build: CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o


# Object files for target gameOfLife.exe
gameOfLife_exe_OBJECTS = \
"CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o"

# External object files for target gameOfLife.exe
gameOfLife_exe_EXTERNAL_OBJECTS =

gameOfLife.exe: CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o
gameOfLife.exe: CMakeFiles/gameOfLife.exe.dir/build.make
gameOfLife.exe: CMakeFiles/gameOfLife.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gameOfLife.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gameOfLife.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gameOfLife.exe.dir/build: gameOfLife.exe

.PHONY : CMakeFiles/gameOfLife.exe.dir/build

CMakeFiles/gameOfLife.exe.dir/requires: CMakeFiles/gameOfLife.exe.dir/gameOfLife.cpp.o.requires

.PHONY : CMakeFiles/gameOfLife.exe.dir/requires

CMakeFiles/gameOfLife.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gameOfLife.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gameOfLife.exe.dir/clean

CMakeFiles/gameOfLife.exe.dir/depend:
	cd "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A2/build/CMakeFiles/gameOfLife.exe.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/gameOfLife.exe.dir/depend

