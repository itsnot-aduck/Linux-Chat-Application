# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = "/home/duki/Materials/Project(s)/linux_chat_application"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/duki/Materials/Project(s)/linux_chat_application/build"

# Include any dependencies generated for this target.
include common/CMakeFiles/common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include common/CMakeFiles/common.dir/compiler_depend.make

# Include the progress variables for this target.
include common/CMakeFiles/common.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/common.dir/flags.make

common/CMakeFiles/common.dir/src/app_cli.c.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/src/app_cli.c.o: ../common/src/app_cli.c
common/CMakeFiles/common.dir/src/app_cli.c.o: common/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/duki/Materials/Project(s)/linux_chat_application/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object common/CMakeFiles/common.dir/src/app_cli.c.o"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT common/CMakeFiles/common.dir/src/app_cli.c.o -MF CMakeFiles/common.dir/src/app_cli.c.o.d -o CMakeFiles/common.dir/src/app_cli.c.o -c "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_cli.c"

common/CMakeFiles/common.dir/src/app_cli.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/src/app_cli.c.i"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_cli.c" > CMakeFiles/common.dir/src/app_cli.c.i

common/CMakeFiles/common.dir/src/app_cli.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/src/app_cli.c.s"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_cli.c" -o CMakeFiles/common.dir/src/app_cli.c.s

common/CMakeFiles/common.dir/src/app_socket.c.o: common/CMakeFiles/common.dir/flags.make
common/CMakeFiles/common.dir/src/app_socket.c.o: ../common/src/app_socket.c
common/CMakeFiles/common.dir/src/app_socket.c.o: common/CMakeFiles/common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/duki/Materials/Project(s)/linux_chat_application/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object common/CMakeFiles/common.dir/src/app_socket.c.o"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT common/CMakeFiles/common.dir/src/app_socket.c.o -MF CMakeFiles/common.dir/src/app_socket.c.o.d -o CMakeFiles/common.dir/src/app_socket.c.o -c "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_socket.c"

common/CMakeFiles/common.dir/src/app_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/common.dir/src/app_socket.c.i"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_socket.c" > CMakeFiles/common.dir/src/app_socket.c.i

common/CMakeFiles/common.dir/src/app_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/common.dir/src/app_socket.c.s"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/duki/Materials/Project(s)/linux_chat_application/common/src/app_socket.c" -o CMakeFiles/common.dir/src/app_socket.c.s

# Object files for target common
common_OBJECTS = \
"CMakeFiles/common.dir/src/app_cli.c.o" \
"CMakeFiles/common.dir/src/app_socket.c.o"

# External object files for target common
common_EXTERNAL_OBJECTS =

common/libcommon.a: common/CMakeFiles/common.dir/src/app_cli.c.o
common/libcommon.a: common/CMakeFiles/common.dir/src/app_socket.c.o
common/libcommon.a: common/CMakeFiles/common.dir/build.make
common/libcommon.a: common/CMakeFiles/common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/duki/Materials/Project(s)/linux_chat_application/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libcommon.a"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean_target.cmake
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/common.dir/build: common/libcommon.a
.PHONY : common/CMakeFiles/common.dir/build

common/CMakeFiles/common.dir/clean:
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/common" && $(CMAKE_COMMAND) -P CMakeFiles/common.dir/cmake_clean.cmake
.PHONY : common/CMakeFiles/common.dir/clean

common/CMakeFiles/common.dir/depend:
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/duki/Materials/Project(s)/linux_chat_application" "/home/duki/Materials/Project(s)/linux_chat_application/common" "/home/duki/Materials/Project(s)/linux_chat_application/build" "/home/duki/Materials/Project(s)/linux_chat_application/build/common" "/home/duki/Materials/Project(s)/linux_chat_application/build/common/CMakeFiles/common.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : common/CMakeFiles/common.dir/depend
