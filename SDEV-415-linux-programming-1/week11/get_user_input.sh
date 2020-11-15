#!/bin/bash

# Write a script called nosy that will do the following:

# a. Ask the user's full name--first, last, and middle name.
echo "Please enter your name (first last middle)"
read first last middle

# b. Greet the user by his or her first name.
echo "Hello $first"

# c. Ask the user's login name and print his or her user ID (from /etc/passwd)
echo "Please enter username"
read username

if ! grep -e "^$username" /etc/passwd >/dev/null; then
echo User $username does not exist
exit
fi

echo "Welcome $username!"

userInfo=$(grep -e "^$username" /etc/passwd)
IFS=":" read -a splitUserInfo <<< $userInfo
user_id=${splitUserInfo[2]}
home_dir=${splitUserInfo[5]}

echo "Your user ID is: $user_id"

# d. Tell the user his or her home directory (the user entered via step c, not currently logged in).
echo "Your home dir is: $home_dir"

# e. Show the user the processes he or she is running (the user entered via step c, not currently logged in user)
echo "Your running processes are:"
ps -u $username

# g. Tell the user the day of the week, and the current time in non-military time.  The output should resemble:
# "The day of the week is Tuesday and the current time is 04:07:38 PM."
day=$(date +%A)
time=`date +"%I:%M:%S %p"`
echo "The day of the week is $day and the current time is $time"
