# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/mathe/CLionProjects/mazerun

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl

# Include any dependencies generated for this target.
include CMakeFiles/MazeRun.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MazeRun.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MazeRun.dir/flags.make

CMakeFiles/MazeRun.dir/src/main.c.o: CMakeFiles/MazeRun.dir/flags.make
CMakeFiles/MazeRun.dir/src/main.c.o: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MazeRun.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MazeRun.dir/src/main.c.o   -c /mnt/c/Users/mathe/CLionProjects/mazerun/src/main.c

CMakeFiles/MazeRun.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MazeRun.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mathe/CLionProjects/mazerun/src/main.c > CMakeFiles/MazeRun.dir/src/main.c.i

CMakeFiles/MazeRun.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MazeRun.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mathe/CLionProjects/mazerun/src/main.c -o CMakeFiles/MazeRun.dir/src/main.c.s

CMakeFiles/MazeRun.dir/src/keyboard.c.o: CMakeFiles/MazeRun.dir/flags.make
CMakeFiles/MazeRun.dir/src/keyboard.c.o: ../src/keyboard.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MazeRun.dir/src/keyboard.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MazeRun.dir/src/keyboard.c.o   -c /mnt/c/Users/mathe/CLionProjects/mazerun/src/keyboard.c

CMakeFiles/MazeRun.dir/src/keyboard.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MazeRun.dir/src/keyboard.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mathe/CLionProjects/mazerun/src/keyboard.c > CMakeFiles/MazeRun.dir/src/keyboard.c.i

CMakeFiles/MazeRun.dir/src/keyboard.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MazeRun.dir/src/keyboard.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mathe/CLionProjects/mazerun/src/keyboard.c -o CMakeFiles/MazeRun.dir/src/keyboard.c.s

CMakeFiles/MazeRun.dir/src/screen.c.o: CMakeFiles/MazeRun.dir/flags.make
CMakeFiles/MazeRun.dir/src/screen.c.o: ../src/screen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MazeRun.dir/src/screen.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MazeRun.dir/src/screen.c.o   -c /mnt/c/Users/mathe/CLionProjects/mazerun/src/screen.c

CMakeFiles/MazeRun.dir/src/screen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MazeRun.dir/src/screen.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mathe/CLionProjects/mazerun/src/screen.c > CMakeFiles/MazeRun.dir/src/screen.c.i

CMakeFiles/MazeRun.dir/src/screen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MazeRun.dir/src/screen.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mathe/CLionProjects/mazerun/src/screen.c -o CMakeFiles/MazeRun.dir/src/screen.c.s

CMakeFiles/MazeRun.dir/src/timer.c.o: CMakeFiles/MazeRun.dir/flags.make
CMakeFiles/MazeRun.dir/src/timer.c.o: ../src/timer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/MazeRun.dir/src/timer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MazeRun.dir/src/timer.c.o   -c /mnt/c/Users/mathe/CLionProjects/mazerun/src/timer.c

CMakeFiles/MazeRun.dir/src/timer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MazeRun.dir/src/timer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/mathe/CLionProjects/mazerun/src/timer.c > CMakeFiles/MazeRun.dir/src/timer.c.i

CMakeFiles/MazeRun.dir/src/timer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MazeRun.dir/src/timer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/mathe/CLionProjects/mazerun/src/timer.c -o CMakeFiles/MazeRun.dir/src/timer.c.s

# Object files for target MazeRun
MazeRun_OBJECTS = \
"CMakeFiles/MazeRun.dir/src/main.c.o" \
"CMakeFiles/MazeRun.dir/src/keyboard.c.o" \
"CMakeFiles/MazeRun.dir/src/screen.c.o" \
"CMakeFiles/MazeRun.dir/src/timer.c.o"

# External object files for target MazeRun
MazeRun_EXTERNAL_OBJECTS =

MazeRun: CMakeFiles/MazeRun.dir/src/main.c.o
MazeRun: CMakeFiles/MazeRun.dir/src/keyboard.c.o
MazeRun: CMakeFiles/MazeRun.dir/src/screen.c.o
MazeRun: CMakeFiles/MazeRun.dir/src/timer.c.o
MazeRun: CMakeFiles/MazeRun.dir/build.make
MazeRun: CMakeFiles/MazeRun.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable MazeRun"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MazeRun.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MazeRun.dir/build: MazeRun

.PHONY : CMakeFiles/MazeRun.dir/build

CMakeFiles/MazeRun.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MazeRun.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MazeRun.dir/clean

CMakeFiles/MazeRun.dir/depend:
	cd /mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/mathe/CLionProjects/mazerun /mnt/c/Users/mathe/CLionProjects/mazerun /mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl /mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl /mnt/c/Users/mathe/CLionProjects/mazerun/cmake-build-debug-wsl/CMakeFiles/MazeRun.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MazeRun.dir/depend

