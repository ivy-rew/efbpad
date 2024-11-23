#!/bin/sh

# Set up fbpad environment vars
export EFBPAD_INSTALL_PREFIX="/mnt/onboard/.adds/efbpad"
export PATH="$EFBPAD_INSTALL_PREFIX/bin:$PATH"
export LD_LIBRARY_PATH="$EFBPAD_INSTALL_PREFIX/lib:$LD_LIBRARY_PATH"

# Of course this should be replaced
export KB_INPUT="/dev/input/event3"

# Go to a landscape orientation
echo 2 > "/sys/class/graphics/fb0/rotate"

# Run fbpad
if [ -c $KB_INPUT ]; then
    kbreader $KB_INPUT | fbpad tmux new-session -A -s main
    RETURN_VALUE=$?
else
    echo "Device $KB_INPUT not found. Doing cleanup and exit."
    RETURN_VALUE=1
fi

# Restore portrait orientation
echo 3 > "/sys/class/graphics/fb0/rotate"

exit ${RETURN_VALUE}

