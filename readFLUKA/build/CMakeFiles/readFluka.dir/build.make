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
CMAKE_SOURCE_DIR = /home/tree/code/QtDemo/FDC_Dealing/readFLUKA

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build

# Include any dependencies generated for this target.
include CMakeFiles/readFluka.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/readFluka.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/readFluka.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/readFluka.dir/flags.make

CMakeFiles/readFluka.dir/cflukadose.cpp.o: CMakeFiles/readFluka.dir/flags.make
CMakeFiles/readFluka.dir/cflukadose.cpp.o: ../cflukadose.cpp
CMakeFiles/readFluka.dir/cflukadose.cpp.o: CMakeFiles/readFluka.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/readFluka.dir/cflukadose.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/readFluka.dir/cflukadose.cpp.o -MF CMakeFiles/readFluka.dir/cflukadose.cpp.o.d -o CMakeFiles/readFluka.dir/cflukadose.cpp.o -c /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/cflukadose.cpp

CMakeFiles/readFluka.dir/cflukadose.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readFluka.dir/cflukadose.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/cflukadose.cpp > CMakeFiles/readFluka.dir/cflukadose.cpp.i

CMakeFiles/readFluka.dir/cflukadose.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readFluka.dir/cflukadose.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/cflukadose.cpp -o CMakeFiles/readFluka.dir/cflukadose.cpp.s

CMakeFiles/readFluka.dir/externdata.cpp.o: CMakeFiles/readFluka.dir/flags.make
CMakeFiles/readFluka.dir/externdata.cpp.o: ../externdata.cpp
CMakeFiles/readFluka.dir/externdata.cpp.o: CMakeFiles/readFluka.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/readFluka.dir/externdata.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/readFluka.dir/externdata.cpp.o -MF CMakeFiles/readFluka.dir/externdata.cpp.o.d -o CMakeFiles/readFluka.dir/externdata.cpp.o -c /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/externdata.cpp

CMakeFiles/readFluka.dir/externdata.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readFluka.dir/externdata.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/externdata.cpp > CMakeFiles/readFluka.dir/externdata.cpp.i

CMakeFiles/readFluka.dir/externdata.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readFluka.dir/externdata.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/externdata.cpp -o CMakeFiles/readFluka.dir/externdata.cpp.s

CMakeFiles/readFluka.dir/main.cpp.o: CMakeFiles/readFluka.dir/flags.make
CMakeFiles/readFluka.dir/main.cpp.o: ../main.cpp
CMakeFiles/readFluka.dir/main.cpp.o: CMakeFiles/readFluka.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/readFluka.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/readFluka.dir/main.cpp.o -MF CMakeFiles/readFluka.dir/main.cpp.o.d -o CMakeFiles/readFluka.dir/main.cpp.o -c /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/main.cpp

CMakeFiles/readFluka.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/readFluka.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/main.cpp > CMakeFiles/readFluka.dir/main.cpp.i

CMakeFiles/readFluka.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/readFluka.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/main.cpp -o CMakeFiles/readFluka.dir/main.cpp.s

# Object files for target readFluka
readFluka_OBJECTS = \
"CMakeFiles/readFluka.dir/cflukadose.cpp.o" \
"CMakeFiles/readFluka.dir/externdata.cpp.o" \
"CMakeFiles/readFluka.dir/main.cpp.o"

# External object files for target readFluka
readFluka_EXTERNAL_OBJECTS =

readFluka: CMakeFiles/readFluka.dir/cflukadose.cpp.o
readFluka: CMakeFiles/readFluka.dir/externdata.cpp.o
readFluka: CMakeFiles/readFluka.dir/main.cpp.o
readFluka: CMakeFiles/readFluka.dir/build.make
readFluka: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
readFluka: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
readFluka: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
readFluka: CMakeFiles/readFluka.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable readFluka"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/readFluka.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/readFluka.dir/build: readFluka
.PHONY : CMakeFiles/readFluka.dir/build

CMakeFiles/readFluka.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/readFluka.dir/cmake_clean.cmake
.PHONY : CMakeFiles/readFluka.dir/clean

CMakeFiles/readFluka.dir/depend:
	cd /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tree/code/QtDemo/FDC_Dealing/readFLUKA /home/tree/code/QtDemo/FDC_Dealing/readFLUKA /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build /home/tree/code/QtDemo/FDC_Dealing/readFLUKA/build/CMakeFiles/readFluka.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/readFluka.dir/depend

