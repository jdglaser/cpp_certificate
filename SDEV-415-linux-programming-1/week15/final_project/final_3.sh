#!/bin/bash

# Final Question 3
# Jarred Glaser
# 2020-12-17
# Menu run datafile program

FILE=datafile3

if [ ! -w "$FILE" ]
then
    echo "File $FILE is not available"
    exit 1
fi

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

delete_entry() {
    read -p "Enter name to delete: " fullname
    if ! (grep -q "^$fullname:" $FILE)
        then
        echo "$fullname does not exist. Please try again."
        return
    fi
    sed -i '/^'"$fullname"':/d' $FILE
    echo "$fullname deleted"
}

view_entry() {
    read -p "Enter name to view: " fullname
    if (grep -q "^$fullname:" $FILE)
        then
        echo $fullname
        grep -n "^$fullname:" $FILE
        return
    else
        echo "$fullname does not exist"
    fi
}

exit_script() {
    echo "Quitting program. Goodbye."
    exit 0;
}

MENU=$'Select an option:\n[1]Add entry\n[2]Delete entry\n[3]View entry\n[4]Exit\n'
while read -ep "$MENU"; do
  case $REPLY in
    1) add_entry;;
    2) delete_entry;;
    3) view_entry;;
    4) exit_script;;
    *) echo "Not a valid option";;
  esac
done