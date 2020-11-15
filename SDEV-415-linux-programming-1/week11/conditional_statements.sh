#!/bin/bash

# Conditional Statements

# Write a script called checking that will do the following:

# a. Take a command-line argument, a user's login name.
# b. Test to see if a command-line argument was provided.
# c. Check to see if the user is in the /etc/passwd file.  If so, the script will print:
# "Found " " in the /etc/passwd file."
# Otherwise, the script will print:
# "No such user on our system" 

if [ "$1" == "" ] || [ $# -gt 1 ]; then
    echo "Parameter 1 is empty"
    exit 0
fi

if ! grep -e "^$1" /etc/passwd >/dev/null; then
    echo No such user on system
    exit
else
    echo "User $1 found in /etc/passwd file!"
fi