# CMake generated Testfile for 
# Source directory: /home/robot/batkin/src/mapping/slam_gmapping/gmapping
# Build directory: /home/robot/batkin/build_isolated/gmapping
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_gmapping_rostest_test_basic_localization_stage.launch "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_stage.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_stage.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_stage.launch ")
add_test(_ctest_gmapping_rostest_test_basic_localization_stage_replay.launch "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_stage_replay.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_stage_replay.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_stage_replay.launch ")
add_test(_ctest_gmapping_rostest_test_basic_localization_stage_replay2.launch "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_stage_replay2.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_stage_replay2.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_stage_replay2.launch ")
add_test(_ctest_gmapping_rostest_test_basic_localization_symmetry.launch "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_symmetry.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_symmetry.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_symmetry.launch ")
add_test(_ctest_gmapping_rostest_test_basic_localization_upside_down.launch "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_upside_down.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_upside_down.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_upside_down.launch ")
add_test(_ctest_gmapping_rostest_test_basic_localization_laser_different_beamcount.test "/home/robot/batkin/build_isolated/gmapping/catkin_generated/env_cached.sh" "/usr/bin/python2" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/robot/batkin/build_isolated/gmapping/test_results/gmapping/rostest-test_basic_localization_laser_different_beamcount.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/robot/batkin/src/mapping/slam_gmapping/gmapping --package=gmapping --results-filename test_basic_localization_laser_different_beamcount.xml --results-base-dir \"/home/robot/batkin/build_isolated/gmapping/test_results\" /home/robot/batkin/src/mapping/slam_gmapping/gmapping/test/basic_localization_laser_different_beamcount.test ")
subdirs("gtest")
