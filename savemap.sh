#! /bin/bash
source ~/batkin/devel_isolated/setup.bash
rosservice call /write_state "{filename: '${HOME}/batkin/src/launch/autolabor_navigation_launch/map/mymap.pbstream'}"
