# Week 5 Discussion Post

*Please provide a brief history of csh, ksh, and bash. Also, identify the differences/similarites of each shell and any of the disadvantages or advantages between the shells. Lastly, provide your recommendation for which shell to use based on your research. Do not forget to justify your recommendation.*

**C Shell (csh)**

+ Created by Berkely Sofware Distribution (BSD) in 1978 by Bill Joy
+ Introduced improvements over Bourne shell
  + History
  + Editing operations
  + Directory stack
  + Job control
  + Tilde completion
+ Syntax resembles the C programming language

**KornShell (ksh)**

+ Developed by David G. Korn at AT&T Bll Labs in 1982
+ Pulls features from both C Shell and Bourne Shell
+ Code is easier to write than C
+ Larger size than ksh and bourne shell but provides better performance
+ Programs written for bourne shell also run with ksh
+ Programmers can add new commands to shell easily

**Bourne Again Shell (bash)**

+ Released in 1989 by Brian Fox as a replacement for the Bourne shell
+ Used as the default login shell for most Linux distributions as well as all releases of Mac OS prior to Catalina
+ Incorporates features from ksh and csh
+ Conforms to POSIX Shell and Tools standard
+ incorporates features for programming and interactive user
  + command line editing
  + unlimited command history
  + job control
  + functions and liases
  + unlimited sized indexed arrays
+ Can run most sh scripts without modification

My shell of choice is the Borne Again Shell or bash. I find this shell to be the most comprehensive in terms of features (especially for programmers) in the list above. It incorporates the best features from both csh and ksh and also includes new features. I also like how it is the default in most Linux systems. This gives the bash shell a lot of great community support and guidance. I have also found bash scripting to be realtively enjoyable and easy to pick up. For these reasons I choose to program using bash.

**References**

(2020). 1.2 Advantages of the Bourne Again Shell. Retreived from https://tldp.org/LDP/Bash-Beginners-Guide/html/sect_01_02.html

(2020). Bash (Unix Shell). Retreived from https://www.wikiwand.com/en/Bash_(Unix_shell)

(2020). C Shell (csh). Retreived from https://www.techopedia.com/definition/6297/c-shell-csh

(2020). KornShell Overview. Retreived from http://www.kornshell.com/info/


## Response Code

Professor,

The following program is a simple bash program that takes a filename variable and reads each line in the file out to the console.

```shell
#!/bin/bash
filename=test.txt

echo "Reading file ${filename} line by line"

while read f
do
    echo $f
done < $filename

# Read last line in file
echo $f 
echo "Done reading file"
```

Given the input file test.txt, which has the contents:

```
hello
this
is
each
line
in
a
file
```

Our output of the above program would be:

```
Reading file test.txt line by line
hello
this
is
each
line
in
a
file
Done reading file
```

