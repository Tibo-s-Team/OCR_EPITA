#!/bin/bash
current=$PWD
# Absolute path to this script, e.g. /home/user/bin/foo.sh
SCRIPT=$(readlink -f "$0")
# Absolute path this script is in, thus /home/user/bin
SCRIPTPATH=$(dirname "$SCRIPT")

if [ $# -ge 1 ];then
    cd $SCRIPTPATH
    cd ../..
    if [ $1 = "--python" ]; then
        echo execute python with args : \"${@:2}\"
    elif [ $1 = "--gcc" ]; then 
        #execute C with rest of the arguments
        make clean && make
        ./TIBO ${@:2}
    else
        echo "Error: Invalid argument: $1"
    fi
else
    clear
    echo "Error: Invalid argument: invalid arg count"
fi

cd $current
