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
CMAKE_SOURCE_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build"

# Include any dependencies generated for this target.
include CMakeFiles/verify_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/verify_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/verify_lib.dir/flags.make

CMakeFiles/verify_lib.dir/Check.cpp.o: CMakeFiles/verify_lib.dir/flags.make
CMakeFiles/verify_lib.dir/Check.cpp.o: ../Check.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/verify_lib.dir/Check.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/verify_lib.dir/Check.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Check.cpp"

CMakeFiles/verify_lib.dir/Check.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/verify_lib.dir/Check.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Check.cpp" > CMakeFiles/verify_lib.dir/Check.cpp.i

CMakeFiles/verify_lib.dir/Check.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/verify_lib.dir/Check.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Check.cpp" -o CMakeFiles/verify_lib.dir/Check.cpp.s

CMakeFiles/verify_lib.dir/Check.cpp.o.requires:

.PHONY : CMakeFiles/verify_lib.dir/Check.cpp.o.requires

CMakeFiles/verify_lib.dir/Check.cpp.o.provides: CMakeFiles/verify_lib.dir/Check.cpp.o.requires
	$(MAKE) -f CMakeFiles/verify_lib.dir/build.make CMakeFiles/verify_lib.dir/Check.cpp.o.provides.build
.PHONY : CMakeFiles/verify_lib.dir/Check.cpp.o.provides

CMakeFiles/verify_lib.dir/Check.cpp.o.provides.build: CMakeFiles/verify_lib.dir/Check.cpp.o


CMakeFiles/verify_lib.dir/Name.cpp.o: CMakeFiles/verify_lib.dir/flags.make
CMakeFiles/verify_lib.dir/Name.cpp.o: ../Name.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/verify_lib.dir/Name.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/verify_lib.dir/Name.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Name.cpp"

CMakeFiles/verify_lib.dir/Name.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/verify_lib.dir/Name.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Name.cpp" > CMakeFiles/verify_lib.dir/Name.cpp.i

CMakeFiles/verify_lib.dir/Name.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/verify_lib.dir/Name.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Name.cpp" -o CMakeFiles/verify_lib.dir/Name.cpp.s

CMakeFiles/verify_lib.dir/Name.cpp.o.requires:

.PHONY : CMakeFiles/verify_lib.dir/Name.cpp.o.requires

CMakeFiles/verify_lib.dir/Name.cpp.o.provides: CMakeFiles/verify_lib.dir/Name.cpp.o.requires
	$(MAKE) -f CMakeFiles/verify_lib.dir/build.make CMakeFiles/verify_lib.dir/Name.cpp.o.provides.build
.PHONY : CMakeFiles/verify_lib.dir/Name.cpp.o.provides

CMakeFiles/verify_lib.dir/Name.cpp.o.provides.build: CMakeFiles/verify_lib.dir/Name.cpp.o


CMakeFiles/verify_lib.dir/Verify.cpp.o: CMakeFiles/verify_lib.dir/flags.make
CMakeFiles/verify_lib.dir/Verify.cpp.o: ../Verify.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/verify_lib.dir/Verify.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/verify_lib.dir/Verify.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Verify.cpp"

CMakeFiles/verify_lib.dir/Verify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/verify_lib.dir/Verify.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Verify.cpp" > CMakeFiles/verify_lib.dir/Verify.cpp.i

CMakeFiles/verify_lib.dir/Verify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/verify_lib.dir/Verify.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/Verify.cpp" -o CMakeFiles/verify_lib.dir/Verify.cpp.s

CMakeFiles/verify_lib.dir/Verify.cpp.o.requires:

.PHONY : CMakeFiles/verify_lib.dir/Verify.cpp.o.requires

CMakeFiles/verify_lib.dir/Verify.cpp.o.provides: CMakeFiles/verify_lib.dir/Verify.cpp.o.requires
	$(MAKE) -f CMakeFiles/verify_lib.dir/build.make CMakeFiles/verify_lib.dir/Verify.cpp.o.provides.build
.PHONY : CMakeFiles/verify_lib.dir/Verify.cpp.o.provides

CMakeFiles/verify_lib.dir/Verify.cpp.o.provides.build: CMakeFiles/verify_lib.dir/Verify.cpp.o


CMakeFiles/verify_lib.dir/ZipInfo.cpp.o: CMakeFiles/verify_lib.dir/flags.make
CMakeFiles/verify_lib.dir/ZipInfo.cpp.o: ../ZipInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/verify_lib.dir/ZipInfo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/verify_lib.dir/ZipInfo.cpp.o -c "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/ZipInfo.cpp"

CMakeFiles/verify_lib.dir/ZipInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/verify_lib.dir/ZipInfo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/ZipInfo.cpp" > CMakeFiles/verify_lib.dir/ZipInfo.cpp.i

CMakeFiles/verify_lib.dir/ZipInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/verify_lib.dir/ZipInfo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/ZipInfo.cpp" -o CMakeFiles/verify_lib.dir/ZipInfo.cpp.s

CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.requires:

.PHONY : CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.requires

CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.provides: CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.requires
	$(MAKE) -f CMakeFiles/verify_lib.dir/build.make CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.provides.build
.PHONY : CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.provides

CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.provides.build: CMakeFiles/verify_lib.dir/ZipInfo.cpp.o


# Object files for target verify_lib
verify_lib_OBJECTS = \
"CMakeFiles/verify_lib.dir/Check.cpp.o" \
"CMakeFiles/verify_lib.dir/Name.cpp.o" \
"CMakeFiles/verify_lib.dir/Verify.cpp.o" \
"CMakeFiles/verify_lib.dir/ZipInfo.cpp.o"

# External object files for target verify_lib
verify_lib_EXTERNAL_OBJECTS =

libverify_lib.a: CMakeFiles/verify_lib.dir/Check.cpp.o
libverify_lib.a: CMakeFiles/verify_lib.dir/Name.cpp.o
libverify_lib.a: CMakeFiles/verify_lib.dir/Verify.cpp.o
libverify_lib.a: CMakeFiles/verify_lib.dir/ZipInfo.cpp.o
libverify_lib.a: CMakeFiles/verify_lib.dir/build.make
libverify_lib.a: CMakeFiles/verify_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libverify_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/verify_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/verify_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/verify_lib.dir/build: libverify_lib.a

.PHONY : CMakeFiles/verify_lib.dir/build

CMakeFiles/verify_lib.dir/requires: CMakeFiles/verify_lib.dir/Check.cpp.o.requires
CMakeFiles/verify_lib.dir/requires: CMakeFiles/verify_lib.dir/Name.cpp.o.requires
CMakeFiles/verify_lib.dir/requires: CMakeFiles/verify_lib.dir/Verify.cpp.o.requires
CMakeFiles/verify_lib.dir/requires: CMakeFiles/verify_lib.dir/ZipInfo.cpp.o.requires

.PHONY : CMakeFiles/verify_lib.dir/requires

CMakeFiles/verify_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/verify_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/verify_lib.dir/clean

CMakeFiles/verify_lib.dir/depend:
	cd "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build" "/home/jonas/Documents/Ugent/Bach/3/2/GPU programmering/Assignment/C2_A1/build/CMakeFiles/verify_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/verify_lib.dir/depend
