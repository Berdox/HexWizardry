# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/hodc/Documents/code/c++/HexWizardry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hodc/Documents/code/c++/HexWizardry/build

# Utility rule file for HexWizardry_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/HexWizardry_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HexWizardry_autogen.dir/progress.make

CMakeFiles/HexWizardry_autogen: HexWizardry_autogen/timestamp

HexWizardry_autogen/timestamp: /usr/lib64/qt6/libexec/moc
HexWizardry_autogen/timestamp: /usr/lib64/qt6/libexec/uic
HexWizardry_autogen/timestamp: CMakeFiles/HexWizardry_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/hodc/Documents/code/c++/HexWizardry/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target HexWizardry"
	/usr/bin/cmake -E cmake_autogen /home/hodc/Documents/code/c++/HexWizardry/build/CMakeFiles/HexWizardry_autogen.dir/AutogenInfo.json Debug
	/usr/bin/cmake -E touch /home/hodc/Documents/code/c++/HexWizardry/build/HexWizardry_autogen/timestamp

HexWizardry_autogen: CMakeFiles/HexWizardry_autogen
HexWizardry_autogen: HexWizardry_autogen/timestamp
HexWizardry_autogen: CMakeFiles/HexWizardry_autogen.dir/build.make
.PHONY : HexWizardry_autogen

# Rule to build all files generated by this target.
CMakeFiles/HexWizardry_autogen.dir/build: HexWizardry_autogen
.PHONY : CMakeFiles/HexWizardry_autogen.dir/build

CMakeFiles/HexWizardry_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HexWizardry_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HexWizardry_autogen.dir/clean

CMakeFiles/HexWizardry_autogen.dir/depend:
	cd /home/hodc/Documents/code/c++/HexWizardry/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hodc/Documents/code/c++/HexWizardry /home/hodc/Documents/code/c++/HexWizardry /home/hodc/Documents/code/c++/HexWizardry/build /home/hodc/Documents/code/c++/HexWizardry/build /home/hodc/Documents/code/c++/HexWizardry/build/CMakeFiles/HexWizardry_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HexWizardry_autogen.dir/depend

