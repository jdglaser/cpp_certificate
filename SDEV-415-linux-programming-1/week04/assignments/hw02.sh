#!/bin/bash
set -x #echo on

# Change your prompt variable to display the current working directory (pwd).  This means that when a directory is changed the prompt also changes to reflect the current directory you are in.
PS1="\w: "

# Set the history to be 100 commands.
export HISTSIZE=100

echo $HISTSIZE

# Set a path for a variable $week4 to be Week4/assignment so that typing cd $week4 will change the working directory to Week4/assignment/
week04=~/Documents/cpp_certificate/SDEV-415-linux-programming-1/week04/assignments

cd $week04

ls

# Set an alias to allow typing h to list the history of commands.
alias h="history"

h

# Set an alias for listlong to be ls –latr.
alias listlong="ls -latr"

listlong

# Set an alias named dir to be ls -aF | more
alias dir="ls -aF | more"

dir

# Set an alias named del to be "rm -i".
alias del="rm -i"

del

