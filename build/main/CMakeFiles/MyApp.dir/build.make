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
include main/CMakeFiles/MyApp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include main/CMakeFiles/MyApp.dir/compiler_depend.make

# Include the progress variables for this target.
include main/CMakeFiles/MyApp.dir/progress.make

# Include the compile flags for this target's objects.
include main/CMakeFiles/MyApp.dir/flags.make

main/CMakeFiles/MyApp.dir/app.c.o: main/CMakeFiles/MyApp.dir/flags.make
main/CMakeFiles/MyApp.dir/app.c.o: ../main/app.c
main/CMakeFiles/MyApp.dir/app.c.o: main/CMakeFiles/MyApp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/duki/Materials/Project(s)/linux_chat_application/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object main/CMakeFiles/MyApp.dir/app.c.o"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/main" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT main/CMakeFiles/MyApp.dir/app.c.o -MF CMakeFiles/MyApp.dir/app.c.o.d -o CMakeFiles/MyApp.dir/app.c.o -c "/home/duki/Materials/Project(s)/linux_chat_application/main/app.c"

main/CMakeFiles/MyApp.dir/app.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MyApp.dir/app.c.i"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/main" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/duki/Materials/Project(s)/linux_chat_application/main/app.c" > CMakeFiles/MyApp.dir/app.c.i

main/CMakeFiles/MyApp.dir/app.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MyApp.dir/app.c.s"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/main" && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/duki/Materials/Project(s)/linux_chat_application/main/app.c" -o CMakeFiles/MyApp.dir/app.c.s

# Object files for target MyApp
MyApp_OBJECTS = \
"CMakeFiles/MyApp.dir/app.c.o"

# External object files for target MyApp
MyApp_EXTERNAL_OBJECTS =

MyApp: main/CMakeFiles/MyApp.dir/app.c.o
MyApp: main/CMakeFiles/MyApp.dir/build.make
MyApp: common/libcommon.a
MyApp: main/CMakeFiles/MyApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/duki/Materials/Project(s)/linux_chat_application/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../MyApp"
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/main" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
main/CMakeFiles/MyApp.dir/build: MyApp
.PHONY : main/CMakeFiles/MyApp.dir/build

main/CMakeFiles/MyApp.dir/clean:
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build/main" && $(CMAKE_COMMAND) -P CMakeFiles/MyApp.dir/cmake_clean.cmake
.PHONY : main/CMakeFiles/MyApp.dir/clean

main/CMakeFiles/MyApp.dir/depend:
	cd "/home/duki/Materials/Project(s)/linux_chat_application/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/duki/Materials/Project(s)/linux_chat_application" "/home/duki/Materials/Project(s)/linux_chat_application/main" "/home/duki/Materials/Project(s)/linux_chat_application/build" "/home/duki/Materials/Project(s)/linux_chat_application/build/main" "/home/duki/Materials/Project(s)/linux_chat_application/build/main/CMakeFiles/MyApp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : main/CMakeFiles/MyApp.dir/depend

