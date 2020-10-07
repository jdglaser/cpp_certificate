# SDEV 415 - Homework Week 5 Answers

1.  Write a bash script called greetme that will do the following:
    a.  Contain a comment section with your name, the name of this script, and the purpose of this script.
    b.  Greet the user (using the correct environment variable)
    c.  Print the date and the time
    d.  Print the value of the TERM, PATH, and HOME variables
    e.  Print Please, could you loan me $50.00?
    f.  Tell the user Good-bye

See `greetme.sh` and `greetme.txt`

2. Answer the following question:

What was the first line of your script?  Why do you need this line?

The first line in my script is:
`#!/bin/bash`

This line is a special line in Linux shell scripts called the **Shebang** that designates the absolute path to the Bash interpreter. This line makes sure that even if I execute the script in another shell (ksh for e.g.) that the script will still use bash if it is installed on the system in `/bin/bash`

**References**

(2020). Shebang. Retreived from https://bash.cyberciti.biz/guide/Shebang.
