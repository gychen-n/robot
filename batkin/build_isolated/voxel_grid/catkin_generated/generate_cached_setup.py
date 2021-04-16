# -*- coding: utf-8 -*-
from __future__ import print_function

import os
import stat
import sys

# find the import for catkin's python package - either from source space or from an installed underlay
if os.path.exists(os.path.join('/opt/ros/kinetic/share/catkin/cmake', 'catkinConfig.cmake.in')):
    sys.path.insert(0, os.path.join('/opt/ros/kinetic/share/catkin/cmake', '..', 'python'))
try:
    from catkin.environment_cache import generate_environment_script
except ImportError:
    # search for catkin package in all workspaces and prepend to path
    for workspace in '/home/robot/batkin/devel_isolated/turtlebot_teleop;/home/robot/batkin/devel_isolated/turtlebot_rapps;/home/robot/batkin/devel_isolated/turtlebot_navigation;/home/robot/batkin/devel_isolated/turtlebot_follower;/home/robot/batkin/devel_isolated/turtlebot_description;/home/robot/batkin/devel_isolated/turtlebot_capabilities;/home/robot/batkin/devel_isolated/turtlebot_calibration;/home/robot/batkin/devel_isolated/turtlebot_bringup;/home/robot/batkin/devel_isolated/turtlebot_apps;/home/robot/batkin/devel_isolated/turtlebot_actions;/home/robot/batkin/devel_isolated/turtlebot;/home/robot/batkin/devel_isolated/tl740d;/home/robot/batkin/devel_isolated/stim;/home/robot/batkin/devel_isolated/stereo_image_proc;/home/robot/batkin/devel_isolated/spacenav_node;/home/robot/batkin/devel_isolated/slam_gmapping;/home/robot/batkin/devel_isolated/simulation_launch;/home/robot/batkin/devel_isolated/rviz_imu_plugin;/home/robot/batkin/devel_isolated/rslidar_sync;/home/robot/batkin/devel_isolated/rslidar_pointcloud;/home/robot/batkin/devel_isolated/rslidar_driver;/home/robot/batkin/devel_isolated/rslidar_msgs;/home/robot/batkin/devel_isolated/rslidar;/home/robot/batkin/devel_isolated/rbx1_apps;/home/robot/batkin/devel_isolated/ps3joy;/home/robot/batkin/devel_isolated/pointcloud_to_laserscan;/home/robot/batkin/devel_isolated/path_rviz_plugin;/home/robot/batkin/devel_isolated/path_server;/home/robot/batkin/devel_isolated/gmapping;/home/robot/batkin/devel_isolated/openslam_gmapping;/home/robot/batkin/devel_isolated/navigation;/home/robot/batkin/devel_isolated/map_server;/home/robot/batkin/devel_isolated/location_fusion;/home/robot/batkin/devel_isolated/joystick_drivers;/home/robot/batkin/devel_isolated/joy_to_twist;/home/robot/batkin/devel_isolated/joy;/home/robot/batkin/devel_isolated/image_view;/home/robot/batkin/devel_isolated/image_rotate;/home/robot/batkin/devel_isolated/image_publisher;/home/robot/batkin/devel_isolated/image_proc;/home/robot/batkin/devel_isolated/image_pipeline;/home/robot/batkin/devel_isolated/freenect_stack;/home/robot/batkin/devel_isolated/freenect_launch;/home/robot/batkin/devel_isolated/freenect_camera;/home/robot/batkin/devel_isolated/fake_localization;/home/robot/batkin/devel_isolated/depth_image_proc;/home/robot/batkin/devel_isolated/dashgo_driver;/home/robot/batkin/devel_isolated/cartographer_rviz;/home/robot/batkin/devel_isolated/cartographer_ros;/home/robot/batkin/devel_isolated/cartographer_ros_msgs;/home/robot/batkin/devel_isolated/camera_calibration;/home/robot/batkin/devel_isolated/autolabor_test_launch;/home/robot/batkin/devel_isolated/autolabor_simulation_object;/home/robot/batkin/devel_isolated/autolabor_simulation_stage;/home/robot/batkin/devel_isolated/autolabor_simulation_location;/home/robot/batkin/devel_isolated/autolabor_simulation_lidar;/home/robot/batkin/devel_isolated/autolabor_simulation_base;/home/robot/batkin/devel_isolated/autolabor_navigation_launch;/home/robot/batkin/devel_isolated/autolabor_keyboard_control;/home/robot/batkin/devel_isolated/autolabor_description;/home/robot/batkin/devel_isolated/ah100b;/home/robot/catkin_ws/devel;/opt/ros/kinetic'.split(';'):
        python_path = os.path.join(workspace, 'lib/python2.7/dist-packages')
        if os.path.isdir(os.path.join(python_path, 'catkin')):
            sys.path.insert(0, python_path)
            break
    from catkin.environment_cache import generate_environment_script

code = generate_environment_script('/home/robot/batkin/devel_isolated/voxel_grid/env.sh')

output_filename = '/home/robot/batkin/build_isolated/voxel_grid/catkin_generated/setup_cached.sh'
with open(output_filename, 'w') as f:
    # print('Generate script for cached setup "%s"' % output_filename)
    f.write('\n'.join(code))

mode = os.stat(output_filename).st_mode
os.chmod(output_filename, mode | stat.S_IXUSR)
