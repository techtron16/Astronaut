# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/astronaut/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/astronaut/catkin_ws/build

# Include any dependencies generated for this target.
include color_tracker/CMakeFiles/color_tracker.dir/depend.make

# Include the progress variables for this target.
include color_tracker/CMakeFiles/color_tracker.dir/progress.make

# Include the compile flags for this target's objects.
include color_tracker/CMakeFiles/color_tracker.dir/flags.make

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o: color_tracker/CMakeFiles/color_tracker.dir/flags.make
color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o: /home/astronaut/catkin_ws/src/color_tracker/src/color_tracker.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/astronaut/catkin_ws/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o"
	cd /home/astronaut/catkin_ws/build/color_tracker && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o -c /home/astronaut/catkin_ws/src/color_tracker/src/color_tracker.cpp

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/color_tracker.dir/src/color_tracker.cpp.i"
	cd /home/astronaut/catkin_ws/build/color_tracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/astronaut/catkin_ws/src/color_tracker/src/color_tracker.cpp > CMakeFiles/color_tracker.dir/src/color_tracker.cpp.i

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/color_tracker.dir/src/color_tracker.cpp.s"
	cd /home/astronaut/catkin_ws/build/color_tracker && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/astronaut/catkin_ws/src/color_tracker/src/color_tracker.cpp -o CMakeFiles/color_tracker.dir/src/color_tracker.cpp.s

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.requires:
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.requires

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.provides: color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.requires
	$(MAKE) -f color_tracker/CMakeFiles/color_tracker.dir/build.make color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.provides.build
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.provides

color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.provides.build: color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o

# Object files for target color_tracker
color_tracker_OBJECTS = \
"CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o"

# External object files for target color_tracker
color_tracker_EXTERNAL_OBJECTS =

/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: color_tracker/CMakeFiles/color_tracker.dir/build.make
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libpcl_ros_filters.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libpcl_ros_io.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libpcl_ros_tf.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_common.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_octree.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_io.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_kdtree.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_search.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_sample_consensus.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_filters.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_features.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_keypoints.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_segmentation.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_visualization.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_outofcore.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_registration.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_recognition.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_surface.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_people.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_tracking.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libpcl_apps.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_serialization.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libqhull.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libOpenNI.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libflann_cpp_s.a
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libvtkCommon.so.5.8.0
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libvtkRendering.so.5.8.0
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libvtkHybrid.so.5.8.0
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libvtkCharts.so.5.8.0
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libdynamic_reconfigure_config_init_mutex.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libnodeletlib.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libbondcpp.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libuuid.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libtinyxml.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libclass_loader.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/libPocoFoundation.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libdl.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libroslib.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librosbag.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librosbag_storage.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_program_options.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libroslz4.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/liblz4.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libtopic_tools.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libtf.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libtf2_ros.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libactionlib.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libmessage_filters.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libroscpp.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libxmlrpcpp.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libtf2.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libroscpp_serialization.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librosconsole.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librosconsole_log4cxx.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librosconsole_backend_interface.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/liblog4cxx.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/librostime.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /opt/ros/indigo/lib/libcpp_common.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
/home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker: color_tracker/CMakeFiles/color_tracker.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable /home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker"
	cd /home/astronaut/catkin_ws/build/color_tracker && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/color_tracker.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
color_tracker/CMakeFiles/color_tracker.dir/build: /home/astronaut/catkin_ws/devel/lib/color_tracker/color_tracker
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/build

color_tracker/CMakeFiles/color_tracker.dir/requires: color_tracker/CMakeFiles/color_tracker.dir/src/color_tracker.cpp.o.requires
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/requires

color_tracker/CMakeFiles/color_tracker.dir/clean:
	cd /home/astronaut/catkin_ws/build/color_tracker && $(CMAKE_COMMAND) -P CMakeFiles/color_tracker.dir/cmake_clean.cmake
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/clean

color_tracker/CMakeFiles/color_tracker.dir/depend:
	cd /home/astronaut/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/astronaut/catkin_ws/src /home/astronaut/catkin_ws/src/color_tracker /home/astronaut/catkin_ws/build /home/astronaut/catkin_ws/build/color_tracker /home/astronaut/catkin_ws/build/color_tracker/CMakeFiles/color_tracker.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : color_tracker/CMakeFiles/color_tracker.dir/depend
