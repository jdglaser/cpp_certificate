#!/bin/bash

# Final Question 2
# Jarred Glaser
# 2020-12-17
# Prompt user to add to datafile

FILE="datafile2"

add_entry() {
    read -p "Enter name to add: " fullname
    if (grep -q "^$fullname:" $FILE); then
        echo "$fullname already exists. Please try again."
        return
    fi
    read -p "Enter phone number: " phone
    read -p "Enter address: " address
    read -p "Enter birthday: " birthday
    read -p "Enter salary: " salary
    final="$fullname:$phone:$address:$birthday:$salary"
    sed -i -e '$a\'"$final" $FILE

    sort -k2 -o $FILE $FILE
    echo "Entry $fullname added"
    grep -n "^$fullname:" $FILE
}

while read -p $'Would you like to add an entry?\n[1]Yes\n[2]No\n'; do
  case $REPLY in
    1) add_entry;;
    2) exit 0;;
    *) echo "Not a valid option";;
  esac
done