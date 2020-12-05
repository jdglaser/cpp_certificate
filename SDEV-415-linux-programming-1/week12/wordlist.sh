#! /bin/bash

echo "Loop through a word list:"
for word in Hello this is a word list
do
    echo $word
done

echo "Loop through args with \"\$@\":"
for arg in "$@"
do
    echo $arg
done