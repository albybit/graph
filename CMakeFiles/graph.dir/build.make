# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/aberto/Downloads/clion-2020.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/aberto/Downloads/clion-2020.2.3/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aberto/graph

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aberto/graph

# Include any dependencies generated for this target.
include CMakeFiles/graph.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graph.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graph.dir/flags.make

CMakeFiles/graph.dir/main.cpp.o: CMakeFiles/graph.dir/flags.make
CMakeFiles/graph.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aberto/graph/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graph.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graph.dir/main.cpp.o -c /home/aberto/graph/main.cpp

CMakeFiles/graph.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aberto/graph/main.cpp > CMakeFiles/graph.dir/main.cpp.i

CMakeFiles/graph.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aberto/graph/main.cpp -o CMakeFiles/graph.dir/main.cpp.s

CMakeFiles/graph.dir/Graph.cpp.o: CMakeFiles/graph.dir/flags.make
CMakeFiles/graph.dir/Graph.cpp.o: Graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aberto/graph/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/graph.dir/Graph.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graph.dir/Graph.cpp.o -c /home/aberto/graph/Graph.cpp

CMakeFiles/graph.dir/Graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/Graph.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aberto/graph/Graph.cpp > CMakeFiles/graph.dir/Graph.cpp.i

CMakeFiles/graph.dir/Graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/Graph.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aberto/graph/Graph.cpp -o CMakeFiles/graph.dir/Graph.cpp.s

CMakeFiles/graph.dir/Path.cpp.o: CMakeFiles/graph.dir/flags.make
CMakeFiles/graph.dir/Path.cpp.o: Path.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/aberto/graph/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/graph.dir/Path.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graph.dir/Path.cpp.o -c /home/aberto/graph/Path.cpp

CMakeFiles/graph.dir/Path.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graph.dir/Path.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aberto/graph/Path.cpp > CMakeFiles/graph.dir/Path.cpp.i

CMakeFiles/graph.dir/Path.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graph.dir/Path.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aberto/graph/Path.cpp -o CMakeFiles/graph.dir/Path.cpp.s

# Object files for target graph
graph_OBJECTS = \
"CMakeFiles/graph.dir/main.cpp.o" \
"CMakeFiles/graph.dir/Graph.cpp.o" \
"CMakeFiles/graph.dir/Path.cpp.o"

# External object files for target graph
graph_EXTERNAL_OBJECTS =

graph: CMakeFiles/graph.dir/main.cpp.o
graph: CMakeFiles/graph.dir/Graph.cpp.o
graph: CMakeFiles/graph.dir/Path.cpp.o
graph: CMakeFiles/graph.dir/build.make
graph: CMakeFiles/graph.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/aberto/graph/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable graph"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graph.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graph.dir/build: graph

.PHONY : CMakeFiles/graph.dir/build

CMakeFiles/graph.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graph.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graph.dir/clean

CMakeFiles/graph.dir/depend:
	cd /home/aberto/graph && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aberto/graph /home/aberto/graph /home/aberto/graph /home/aberto/graph /home/aberto/graph/CMakeFiles/graph.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graph.dir/depend

