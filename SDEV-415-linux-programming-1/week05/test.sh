#!/bin/bash
filename=test.txt

echo "Reading file ${filename} line by line"

while read f
do
    echo $f
done < $filename

# Read last line in file
echo $f 
echo "Done reading file"