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
CMAKE_SOURCE_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build"

# Include any dependencies generated for this target.
include CMakeFiles/decipher.exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/decipher.exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/decipher.exe.dir/flags.make

CMakeFiles/decipher.exe.dir/Decipher.cpp.o: CMakeFiles/decipher.exe.dir/flags.make
CMakeFiles/decipher.exe.dir/Decipher.cpp.o: ../Decipher.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/decipher.exe.dir/Decipher.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/decipher.exe.dir/Decipher.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/Decipher.cpp"

CMakeFiles/decipher.exe.dir/Decipher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/decipher.exe.dir/Decipher.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/Decipher.cpp" > CMakeFiles/decipher.exe.dir/Decipher.cpp.i

CMakeFiles/decipher.exe.dir/Decipher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/decipher.exe.dir/Decipher.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/Decipher.cpp" -o CMakeFiles/decipher.exe.dir/Decipher.cpp.s

CMakeFiles/decipher.exe.dir/Decipher.cpp.o.requires:

.PHONY : CMakeFiles/decipher.exe.dir/Decipher.cpp.o.requires

CMakeFiles/decipher.exe.dir/Decipher.cpp.o.provides: CMakeFiles/decipher.exe.dir/Decipher.cpp.o.requires
	$(MAKE) -f CMakeFiles/decipher.exe.dir/build.make CMakeFiles/decipher.exe.dir/Decipher.cpp.o.provides.build
.PHONY : CMakeFiles/decipher.exe.dir/Decipher.cpp.o.provides

CMakeFiles/decipher.exe.dir/Decipher.cpp.o.provides.build: CMakeFiles/decipher.exe.dir/Decipher.cpp.o


# Object files for target decipher.exe
decipher_exe_OBJECTS = \
"CMakeFiles/decipher.exe.dir/Decipher.cpp.o"

# External object files for target decipher.exe
decipher_exe_EXTERNAL_OBJECTS =

decipher.exe: CMakeFiles/decipher.exe.dir/Decipher.cpp.o
decipher.exe: CMakeFiles/decipher.exe.dir/build.make
decipher.exe: CMakeFiles/decipher.exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable decipher.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/decipher.exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/decipher.exe.dir/build: decipher.exe

.PHONY : CMakeFiles/decipher.exe.dir/build

CMakeFiles/decipher.exe.dir/requires: CMakeFiles/decipher.exe.dir/Decipher.cpp.o.requires

.PHONY : CMakeFiles/decipher.exe.dir/requires

CMakeFiles/decipher.exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/decipher.exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/decipher.exe.dir/clean

CMakeFiles/decipher.exe.dir/depend:
	cd "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C1_A2/build/CMakeFiles/decipher.exe.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/decipher.exe.dir/depend

