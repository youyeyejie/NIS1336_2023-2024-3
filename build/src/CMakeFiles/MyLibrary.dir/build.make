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
CMAKE_SOURCE_DIR = /home/code/Desktop/git/NIS1336_2023-2024-3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/code/Desktop/git/NIS1336_2023-2024-3/build

# Include any dependencies generated for this target.
include src/CMakeFiles/MyLibrary.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/MyLibrary.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/MyLibrary.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/MyLibrary.dir/flags.make

src/CMakeFiles/MyLibrary.dir/Account.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/Account.cpp.o: ../src/Account.cpp
src/CMakeFiles/MyLibrary.dir/Account.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/MyLibrary.dir/Account.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/Account.cpp.o -MF CMakeFiles/MyLibrary.dir/Account.cpp.o.d -o CMakeFiles/MyLibrary.dir/Account.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/Account.cpp

src/CMakeFiles/MyLibrary.dir/Account.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/Account.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/Account.cpp > CMakeFiles/MyLibrary.dir/Account.cpp.i

src/CMakeFiles/MyLibrary.dir/Account.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/Account.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/Account.cpp -o CMakeFiles/MyLibrary.dir/Account.cpp.s

src/CMakeFiles/MyLibrary.dir/cli.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/cli.cpp.o: ../src/cli.cpp
src/CMakeFiles/MyLibrary.dir/cli.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/MyLibrary.dir/cli.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/cli.cpp.o -MF CMakeFiles/MyLibrary.dir/cli.cpp.o.d -o CMakeFiles/MyLibrary.dir/cli.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/cli.cpp

src/CMakeFiles/MyLibrary.dir/cli.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/cli.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/cli.cpp > CMakeFiles/MyLibrary.dir/cli.cpp.i

src/CMakeFiles/MyLibrary.dir/cli.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/cli.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/cli.cpp -o CMakeFiles/MyLibrary.dir/cli.cpp.s

src/CMakeFiles/MyLibrary.dir/task.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/task.cpp.o: ../src/task.cpp
src/CMakeFiles/MyLibrary.dir/task.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/MyLibrary.dir/task.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/task.cpp.o -MF CMakeFiles/MyLibrary.dir/task.cpp.o.d -o CMakeFiles/MyLibrary.dir/task.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/task.cpp

src/CMakeFiles/MyLibrary.dir/task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/task.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/task.cpp > CMakeFiles/MyLibrary.dir/task.cpp.i

src/CMakeFiles/MyLibrary.dir/task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/task.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/task.cpp -o CMakeFiles/MyLibrary.dir/task.cpp.s

src/CMakeFiles/MyLibrary.dir/run.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/run.cpp.o: ../src/run.cpp
src/CMakeFiles/MyLibrary.dir/run.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/MyLibrary.dir/run.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/run.cpp.o -MF CMakeFiles/MyLibrary.dir/run.cpp.o.d -o CMakeFiles/MyLibrary.dir/run.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/run.cpp

src/CMakeFiles/MyLibrary.dir/run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/run.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/run.cpp > CMakeFiles/MyLibrary.dir/run.cpp.i

src/CMakeFiles/MyLibrary.dir/run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/run.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/run.cpp -o CMakeFiles/MyLibrary.dir/run.cpp.s

src/CMakeFiles/MyLibrary.dir/thread1.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/thread1.cpp.o: ../src/thread1.cpp
src/CMakeFiles/MyLibrary.dir/thread1.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/MyLibrary.dir/thread1.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/thread1.cpp.o -MF CMakeFiles/MyLibrary.dir/thread1.cpp.o.d -o CMakeFiles/MyLibrary.dir/thread1.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread1.cpp

src/CMakeFiles/MyLibrary.dir/thread1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/thread1.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread1.cpp > CMakeFiles/MyLibrary.dir/thread1.cpp.i

src/CMakeFiles/MyLibrary.dir/thread1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/thread1.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread1.cpp -o CMakeFiles/MyLibrary.dir/thread1.cpp.s

src/CMakeFiles/MyLibrary.dir/thread2.cpp.o: src/CMakeFiles/MyLibrary.dir/flags.make
src/CMakeFiles/MyLibrary.dir/thread2.cpp.o: ../src/thread2.cpp
src/CMakeFiles/MyLibrary.dir/thread2.cpp.o: src/CMakeFiles/MyLibrary.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/MyLibrary.dir/thread2.cpp.o"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/MyLibrary.dir/thread2.cpp.o -MF CMakeFiles/MyLibrary.dir/thread2.cpp.o.d -o CMakeFiles/MyLibrary.dir/thread2.cpp.o -c /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread2.cpp

src/CMakeFiles/MyLibrary.dir/thread2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyLibrary.dir/thread2.cpp.i"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread2.cpp > CMakeFiles/MyLibrary.dir/thread2.cpp.i

src/CMakeFiles/MyLibrary.dir/thread2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyLibrary.dir/thread2.cpp.s"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/code/Desktop/git/NIS1336_2023-2024-3/src/thread2.cpp -o CMakeFiles/MyLibrary.dir/thread2.cpp.s

# Object files for target MyLibrary
MyLibrary_OBJECTS = \
"CMakeFiles/MyLibrary.dir/Account.cpp.o" \
"CMakeFiles/MyLibrary.dir/cli.cpp.o" \
"CMakeFiles/MyLibrary.dir/task.cpp.o" \
"CMakeFiles/MyLibrary.dir/run.cpp.o" \
"CMakeFiles/MyLibrary.dir/thread1.cpp.o" \
"CMakeFiles/MyLibrary.dir/thread2.cpp.o"

# External object files for target MyLibrary
MyLibrary_EXTERNAL_OBJECTS =

src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/Account.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/cli.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/task.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/run.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/thread1.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/thread2.cpp.o
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/build.make
src/libMyLibrary.a: src/CMakeFiles/MyLibrary.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/code/Desktop/git/NIS1336_2023-2024-3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library libMyLibrary.a"
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MyLibrary.dir/cmake_clean_target.cmake
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyLibrary.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/MyLibrary.dir/build: src/libMyLibrary.a
.PHONY : src/CMakeFiles/MyLibrary.dir/build

src/CMakeFiles/MyLibrary.dir/clean:
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build/src && $(CMAKE_COMMAND) -P CMakeFiles/MyLibrary.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/MyLibrary.dir/clean

src/CMakeFiles/MyLibrary.dir/depend:
	cd /home/code/Desktop/git/NIS1336_2023-2024-3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/code/Desktop/git/NIS1336_2023-2024-3 /home/code/Desktop/git/NIS1336_2023-2024-3/src /home/code/Desktop/git/NIS1336_2023-2024-3/build /home/code/Desktop/git/NIS1336_2023-2024-3/build/src /home/code/Desktop/git/NIS1336_2023-2024-3/build/src/CMakeFiles/MyLibrary.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/MyLibrary.dir/depend

