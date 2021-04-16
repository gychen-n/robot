#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/robot/batkin/src/tool/image_pipeline/camera_calibration"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/robot/batkin/install_isolated/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/robot/batkin/install_isolated/lib/python2.7/dist-packages:/home/robot/batkin/build_isolated/camera_calibration/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/robot/batkin/build_isolated/camera_calibration" \
    "/usr/bin/python2" \
    "/home/robot/batkin/src/tool/image_pipeline/camera_calibration/setup.py" \
     \
    build --build-base "/home/robot/batkin/build_isolated/camera_calibration" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/robot/batkin/install_isolated" --install-scripts="/home/robot/batkin/install_isolated/bin"
