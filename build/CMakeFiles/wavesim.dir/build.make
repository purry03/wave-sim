# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/perry/fluid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/perry/fluid/build

# Include any dependencies generated for this target.
include CMakeFiles/wavesim.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wavesim.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wavesim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wavesim.dir/flags.make

CMakeFiles/wavesim.dir/src/main.cpp.o: CMakeFiles/wavesim.dir/flags.make
CMakeFiles/wavesim.dir/src/main.cpp.o: /home/perry/fluid/src/main.cpp
CMakeFiles/wavesim.dir/src/main.cpp.o: CMakeFiles/wavesim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/perry/fluid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wavesim.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wavesim.dir/src/main.cpp.o -MF CMakeFiles/wavesim.dir/src/main.cpp.o.d -o CMakeFiles/wavesim.dir/src/main.cpp.o -c /home/perry/fluid/src/main.cpp

CMakeFiles/wavesim.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wavesim.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perry/fluid/src/main.cpp > CMakeFiles/wavesim.dir/src/main.cpp.i

CMakeFiles/wavesim.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wavesim.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perry/fluid/src/main.cpp -o CMakeFiles/wavesim.dir/src/main.cpp.s

CMakeFiles/wavesim.dir/src/renderer.cpp.o: CMakeFiles/wavesim.dir/flags.make
CMakeFiles/wavesim.dir/src/renderer.cpp.o: /home/perry/fluid/src/renderer.cpp
CMakeFiles/wavesim.dir/src/renderer.cpp.o: CMakeFiles/wavesim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/perry/fluid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wavesim.dir/src/renderer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wavesim.dir/src/renderer.cpp.o -MF CMakeFiles/wavesim.dir/src/renderer.cpp.o.d -o CMakeFiles/wavesim.dir/src/renderer.cpp.o -c /home/perry/fluid/src/renderer.cpp

CMakeFiles/wavesim.dir/src/renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wavesim.dir/src/renderer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perry/fluid/src/renderer.cpp > CMakeFiles/wavesim.dir/src/renderer.cpp.i

CMakeFiles/wavesim.dir/src/renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wavesim.dir/src/renderer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perry/fluid/src/renderer.cpp -o CMakeFiles/wavesim.dir/src/renderer.cpp.s

CMakeFiles/wavesim.dir/src/fluid.cpp.o: CMakeFiles/wavesim.dir/flags.make
CMakeFiles/wavesim.dir/src/fluid.cpp.o: /home/perry/fluid/src/fluid.cpp
CMakeFiles/wavesim.dir/src/fluid.cpp.o: CMakeFiles/wavesim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/perry/fluid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wavesim.dir/src/fluid.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wavesim.dir/src/fluid.cpp.o -MF CMakeFiles/wavesim.dir/src/fluid.cpp.o.d -o CMakeFiles/wavesim.dir/src/fluid.cpp.o -c /home/perry/fluid/src/fluid.cpp

CMakeFiles/wavesim.dir/src/fluid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wavesim.dir/src/fluid.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perry/fluid/src/fluid.cpp > CMakeFiles/wavesim.dir/src/fluid.cpp.i

CMakeFiles/wavesim.dir/src/fluid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wavesim.dir/src/fluid.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perry/fluid/src/fluid.cpp -o CMakeFiles/wavesim.dir/src/fluid.cpp.s

CMakeFiles/wavesim.dir/src/random.cpp.o: CMakeFiles/wavesim.dir/flags.make
CMakeFiles/wavesim.dir/src/random.cpp.o: /home/perry/fluid/src/random.cpp
CMakeFiles/wavesim.dir/src/random.cpp.o: CMakeFiles/wavesim.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/perry/fluid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wavesim.dir/src/random.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wavesim.dir/src/random.cpp.o -MF CMakeFiles/wavesim.dir/src/random.cpp.o.d -o CMakeFiles/wavesim.dir/src/random.cpp.o -c /home/perry/fluid/src/random.cpp

CMakeFiles/wavesim.dir/src/random.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wavesim.dir/src/random.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/perry/fluid/src/random.cpp > CMakeFiles/wavesim.dir/src/random.cpp.i

CMakeFiles/wavesim.dir/src/random.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wavesim.dir/src/random.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/perry/fluid/src/random.cpp -o CMakeFiles/wavesim.dir/src/random.cpp.s

# Object files for target wavesim
wavesim_OBJECTS = \
"CMakeFiles/wavesim.dir/src/main.cpp.o" \
"CMakeFiles/wavesim.dir/src/renderer.cpp.o" \
"CMakeFiles/wavesim.dir/src/fluid.cpp.o" \
"CMakeFiles/wavesim.dir/src/random.cpp.o"

# External object files for target wavesim
wavesim_EXTERNAL_OBJECTS =

wavesim: CMakeFiles/wavesim.dir/src/main.cpp.o
wavesim: CMakeFiles/wavesim.dir/src/renderer.cpp.o
wavesim: CMakeFiles/wavesim.dir/src/fluid.cpp.o
wavesim: CMakeFiles/wavesim.dir/src/random.cpp.o
wavesim: CMakeFiles/wavesim.dir/build.make
wavesim: /usr/lib/x86_64-linux-gnu/libpython3.12.so
wavesim: CMakeFiles/wavesim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/perry/fluid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable wavesim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wavesim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wavesim.dir/build: wavesim
.PHONY : CMakeFiles/wavesim.dir/build

CMakeFiles/wavesim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wavesim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wavesim.dir/clean

CMakeFiles/wavesim.dir/depend:
	cd /home/perry/fluid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/perry/fluid /home/perry/fluid /home/perry/fluid/build /home/perry/fluid/build /home/perry/fluid/build/CMakeFiles/wavesim.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/wavesim.dir/depend

