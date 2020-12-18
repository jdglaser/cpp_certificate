#!/bin/bash

# Final Question 1
# Jarred Glaser
# 2020-12-17
# Display datafile in sorted order.

FILE=datafile

# Sort by last name
sort -k2 $FILE

# Show contents of file
cat $FILE

echo
entries=$(wc -l $FILE | tr -dc '0-9')
entries=$((entries+1))
echo "There are $entries entries"