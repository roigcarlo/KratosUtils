# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/roigcarlo/KratosUtils/Snippets/AutoRegister

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/roigcarlo/KratosUtils/Snippets/AutoRegister

# Include any dependencies generated for this target.
include CMakeFiles/auto_register.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/auto_register.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/auto_register.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/auto_register.dir/flags.make

CMakeFiles/auto_register.dir/register.cpp.o: CMakeFiles/auto_register.dir/flags.make
CMakeFiles/auto_register.dir/register.cpp.o: register.cpp
CMakeFiles/auto_register.dir/register.cpp.o: CMakeFiles/auto_register.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/roigcarlo/KratosUtils/Snippets/AutoRegister/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/auto_register.dir/register.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/auto_register.dir/register.cpp.o -MF CMakeFiles/auto_register.dir/register.cpp.o.d -o CMakeFiles/auto_register.dir/register.cpp.o -c /home/roigcarlo/KratosUtils/Snippets/AutoRegister/register.cpp

CMakeFiles/auto_register.dir/register.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/auto_register.dir/register.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/roigcarlo/KratosUtils/Snippets/AutoRegister/register.cpp > CMakeFiles/auto_register.dir/register.cpp.i

CMakeFiles/auto_register.dir/register.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/auto_register.dir/register.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/roigcarlo/KratosUtils/Snippets/AutoRegister/register.cpp -o CMakeFiles/auto_register.dir/register.cpp.s

# Object files for target auto_register
auto_register_OBJECTS = \
"CMakeFiles/auto_register.dir/register.cpp.o"

# External object files for target auto_register
auto_register_EXTERNAL_OBJECTS =

auto_register: CMakeFiles/auto_register.dir/register.cpp.o
auto_register: CMakeFiles/auto_register.dir/build.make
auto_register: CMakeFiles/auto_register.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/roigcarlo/KratosUtils/Snippets/AutoRegister/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable auto_register"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/auto_register.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/auto_register.dir/build: auto_register
.PHONY : CMakeFiles/auto_register.dir/build

CMakeFiles/auto_register.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/auto_register.dir/cmake_clean.cmake
.PHONY : CMakeFiles/auto_register.dir/clean

CMakeFiles/auto_register.dir/depend:
	cd /home/roigcarlo/KratosUtils/Snippets/AutoRegister && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/roigcarlo/KratosUtils/Snippets/AutoRegister /home/roigcarlo/KratosUtils/Snippets/AutoRegister /home/roigcarlo/KratosUtils/Snippets/AutoRegister /home/roigcarlo/KratosUtils/Snippets/AutoRegister /home/roigcarlo/KratosUtils/Snippets/AutoRegister/CMakeFiles/auto_register.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/auto_register.dir/depend
