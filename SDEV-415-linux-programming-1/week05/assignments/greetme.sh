#!/bin/bash

# a) Contain a comment section with your name, the name of this script, and the purpose of this script.
#===============================#
# Greet Me Bash Script
# Script for SDEV-415 HW Week 5
# Jarred Glaser
#===============================#

# b) Greet the user (using the correct environment variable)
echo "Hello ${USER}!"

# c) Print the date and the time
echo "$(date)"

# d) Print the value of the TERM, PATH, and HOME variables
echo $TERM
echo $PATH
echo $HOME

# e) Print Please, could you loan me $50.00?
echo "Please, could you loan me \$50.00?"

# f) Tell the user Good-bye
echo "Good-bye"