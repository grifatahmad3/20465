# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = /home/user/.cache/JetBrains/RemoteDev/dist/7c26c46eeb42c_CLion-242.20224.214/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/user/.cache/JetBrains/RemoteDev/dist/7c26c46eeb42c_CLion-242.20224.214/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/user/projects/20465/14

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/projects/20465/14/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/myassm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/myassm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/myassm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/myassm.dir/flags.make

CMakeFiles/myassm.dir/myassm.c.o: CMakeFiles/myassm.dir/flags.make
CMakeFiles/myassm.dir/myassm.c.o: /home/user/projects/20465/14/myassm.c
CMakeFiles/myassm.dir/myassm.c.o: CMakeFiles/myassm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/projects/20465/14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/myassm.dir/myassm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myassm.dir/myassm.c.o -MF CMakeFiles/myassm.dir/myassm.c.o.d -o CMakeFiles/myassm.dir/myassm.c.o -c /home/user/projects/20465/14/myassm.c

CMakeFiles/myassm.dir/myassm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/myassm.dir/myassm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/projects/20465/14/myassm.c > CMakeFiles/myassm.dir/myassm.c.i

CMakeFiles/myassm.dir/myassm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/myassm.dir/myassm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/projects/20465/14/myassm.c -o CMakeFiles/myassm.dir/myassm.c.s

CMakeFiles/myassm.dir/essentials.c.o: CMakeFiles/myassm.dir/flags.make
CMakeFiles/myassm.dir/essentials.c.o: /home/user/projects/20465/14/essentials.c
CMakeFiles/myassm.dir/essentials.c.o: CMakeFiles/myassm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/projects/20465/14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/myassm.dir/essentials.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myassm.dir/essentials.c.o -MF CMakeFiles/myassm.dir/essentials.c.o.d -o CMakeFiles/myassm.dir/essentials.c.o -c /home/user/projects/20465/14/essentials.c

CMakeFiles/myassm.dir/essentials.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/myassm.dir/essentials.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/projects/20465/14/essentials.c > CMakeFiles/myassm.dir/essentials.c.i

CMakeFiles/myassm.dir/essentials.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/myassm.dir/essentials.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/projects/20465/14/essentials.c -o CMakeFiles/myassm.dir/essentials.c.s

CMakeFiles/myassm.dir/preasm.c.o: CMakeFiles/myassm.dir/flags.make
CMakeFiles/myassm.dir/preasm.c.o: /home/user/projects/20465/14/preasm.c
CMakeFiles/myassm.dir/preasm.c.o: CMakeFiles/myassm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/projects/20465/14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/myassm.dir/preasm.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myassm.dir/preasm.c.o -MF CMakeFiles/myassm.dir/preasm.c.o.d -o CMakeFiles/myassm.dir/preasm.c.o -c /home/user/projects/20465/14/preasm.c

CMakeFiles/myassm.dir/preasm.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/myassm.dir/preasm.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/projects/20465/14/preasm.c > CMakeFiles/myassm.dir/preasm.c.i

CMakeFiles/myassm.dir/preasm.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/myassm.dir/preasm.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/projects/20465/14/preasm.c -o CMakeFiles/myassm.dir/preasm.c.s

CMakeFiles/myassm.dir/firstpass.c.o: CMakeFiles/myassm.dir/flags.make
CMakeFiles/myassm.dir/firstpass.c.o: /home/user/projects/20465/14/firstpass.c
CMakeFiles/myassm.dir/firstpass.c.o: CMakeFiles/myassm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/user/projects/20465/14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/myassm.dir/firstpass.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/myassm.dir/firstpass.c.o -MF CMakeFiles/myassm.dir/firstpass.c.o.d -o CMakeFiles/myassm.dir/firstpass.c.o -c /home/user/projects/20465/14/firstpass.c

CMakeFiles/myassm.dir/firstpass.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/myassm.dir/firstpass.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/user/projects/20465/14/firstpass.c > CMakeFiles/myassm.dir/firstpass.c.i

CMakeFiles/myassm.dir/firstpass.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/myassm.dir/firstpass.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/user/projects/20465/14/firstpass.c -o CMakeFiles/myassm.dir/firstpass.c.s

# Object files for target myassm
myassm_OBJECTS = \
"CMakeFiles/myassm.dir/myassm.c.o" \
"CMakeFiles/myassm.dir/essentials.c.o" \
"CMakeFiles/myassm.dir/preasm.c.o" \
"CMakeFiles/myassm.dir/firstpass.c.o"

# External object files for target myassm
myassm_EXTERNAL_OBJECTS =

myassm: CMakeFiles/myassm.dir/myassm.c.o
myassm: CMakeFiles/myassm.dir/essentials.c.o
myassm: CMakeFiles/myassm.dir/preasm.c.o
myassm: CMakeFiles/myassm.dir/firstpass.c.o
myassm: CMakeFiles/myassm.dir/build.make
myassm: CMakeFiles/myassm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/user/projects/20465/14/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable myassm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myassm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/myassm.dir/build: myassm
.PHONY : CMakeFiles/myassm.dir/build

CMakeFiles/myassm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/myassm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/myassm.dir/clean

CMakeFiles/myassm.dir/depend:
	cd /home/user/projects/20465/14/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/projects/20465/14 /home/user/projects/20465/14 /home/user/projects/20465/14/cmake-build-debug /home/user/projects/20465/14/cmake-build-debug /home/user/projects/20465/14/cmake-build-debug/CMakeFiles/myassm.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/myassm.dir/depend

