#!/bin/bash
echo "Hello, please provide a file to move (include full path): " 
read file
if [ ! -f "$file" ]; then
    echo "$file does not exist."
    exit 1
fi

echo 