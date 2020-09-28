# SDEV-415 Week 04 Homework

1. *Create a directory structure for the work you do in this class. The directory structure should include a top-level directory (located in your home directory) named “Linux Programming I”. You then need to create sub-directories inside this directory for each week. (week1, week2, all the way up to week15).  Lastly, create Assignment directories in each “weekN” directory. You will need to use the mkdir and cd commands to do this.  You should also use the ls command to demonstrate the creation of the directory structure.*

- See script `hw01.sh` which executes all of the required commands. The output can be seen in `hw01.txt`

2. *Perform the following:*
   - *Change your prompt variable to display the current working directory (pwd).  This means that when a directory is changed the prompt also changes to reflect the current directory you are in.*
   - *Set the history to be 100 commands.*
   - *Set a path for a variable $week4 to be Week4/assignment so that typing cd $week4 will change the working directory to Week4/assignment/*
   - *Set an alias to allow typing h to list the history of commands.*
   - *Set an alias for listlong to be ls –latr.*
   - *Set an alias named dir to be ls -aF | more*
   - *Set an alias named del to be "rm -i".*

- See script `hw02.sh` for a list of commands executed. The output of each command can be seen in `hw02.txt`

3. *Display the values of your TERM and HOME environment variables to the screen.*

- See script `hw03.sh` for shell script. The output can be seen in `hw03.txt`

4. *Hit the CTRL-D key combination. Note what happens.*

   - *If the ignoreeof variable was not set, you should have been logged off of the computer system.  Now set the ignoreeof variable (enable it).  Then hit the CTRL-D key combination.  What happens this time?*

- With the IGNOREE variable set the command only warns me instead of closing the terminal. I set the command to `2` (`export IGNOREE=2`) and this made the Ctrl+D prompt a warning twice before closing.

5. *Perform ‘man’ writing the contents of man to a file, for the following items: bash, csh, korn. Submit the output file of the man contents.  Use redirection to do this.  If your system does not include the above specified man pages, please install it.*

- See script `hw05.sh` for shell script. Output for man contents in manoutput.txt

6. *Get a listing of the contents of /usr/local/bin using the ls command. Redirect the output from the ls command to a file, ~/ls_output. (Where is that file located?)*

   - *Use the wc command to count the number of lines in the ls_output file.*
   - *(If there are no files in this directory, then try /usr/bin or a directory that contains many files)*
   - *Re-do the above by omitting the redirection to ls_output and use | (a "pipe") to connect the output of ls to the input of wc.*

- See script `hw06.sh` for shell script. The output can be seen in `hw06.txt`. The ls_output file will be located in the home directory which is aliased by `~/`.

7. *Display the current number of processes running on your system using any number of commands and a pipe.  I want the number, not just a list of processes.*

- See script `hw07.sh` for shell script. The output can be seen in `hw07.txt`.

8. *Explain the difference between “>” and “>>” when using redirection.   Also, what does the “!” command do.  Give me an example and its output.*

- The `>` redirection operator writes output from a command to a file, creating the file if needed and overwriting any data previously in that file. The `>>` operator does the same, but instead it appends to the file if it already exists. 
- The `!` operator is the logical `not` operator. We can use this operator to exclude results from a command. For example, if we want to list all files in the directory except text files, we would use:

```shell
ls !(*.txt)
```
