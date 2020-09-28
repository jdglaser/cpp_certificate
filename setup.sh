#!/bin/bash
set -x #echo on

echo "Creating contents for class Linux Programming 1"

echo "Creating directory"

ROOT_NAME="SDEV-415-linux-programming-1"
echo $ROOT_NAME
mkdir $ROOT_NAME

echo "Directory $ROOT_NAME created"

cd $ROOT_NAME
for i in $(seq -f "%02g" 1 15)
do
    mkdir "week$i"

    cd "week$i"
    mkdir "notes"
    mkdir "assignments"
    echo "week$i created"
    cd ..
done

echo "Listing created directory structure"
ls