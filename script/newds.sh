#!/bin/bash
# newds.sh
if [ $# -ne 1 ];then
    echo "usage: ./newds.sh SqList"
    exit 1
fi
NAME=$1
touch include/${NAME}.h src/${NAME}.c
echo "Created include/$NAME.h and src/$NAME.c"
