#!/bin/bash
current=$PWD
src = ../ # attention : erreur si pas dans le bon directory !

if [ $# -eq 1 ];then
    cd $src
    if [ $1 = "--python" ]; then
        #execute python with the rest of the args
    elif [[ ${$1:0:2} != "--" ]] 
        #execute C with rest of the arguments
        make clean && make
    else
        echo "Error: Invalid argument: $1"
    fi
else
    clear
    echo "Error: Invalid argument: invalid arg count"
fi

cd $current
