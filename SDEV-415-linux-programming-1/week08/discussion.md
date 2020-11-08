# Discussion Week 8

The `sed` command is a really powerful utility in Linux that allows us to stream over text and apply manipulations and actions on the text. 

The commands I've chosen this week will use this example text I created, which is in a file titles `hello.txt`:

One very useful feature of sed is to use it to replace all occurences of a word or phrase in a text stream. This is similar to how we might use find and replace in Microsoft Word and other text editor programs. For example, in the below text, labeled `hello.txt` if we wanted to replace "hello" with "goodbye", we would use the following command.

**hello.txt**
```
hello this is a test file
we like to say hello world when testing code
it is important to say hello when you greet someone
```

```sh
sed "s/hello/goodbye/g" hello.txt
```

This produces the output:

```
goodbye this is a test file
we like to say goodbye world when testing code
it is important to say goodbye when you greet someone
```

As we can see the command works really well to replace some phrase with something else in the text. An important note about the example is that we end the replacement phrase with a `/g`. This tells sed to replace globally, meaning that all occurences of a word in a line will be replaced. If instead our example text was:

```
hello hello hello
```

and we didn't include the global flag, instead running:

```sh
sed "s/hello/goodbye/" hello.txt
```

we would get the output:

```
goodbye hello hello
```

As we can see, only the first occurence is replaced.

Another useful command with sed is to output lines that have a matching pattern to something we are searching for. Let's take a look at a new example text below.

**hello2.txt**
```
hello this is a test file
we like to say hello world when testing code
it is important to say hello when you greet someone
this line doesn't have anything cool in it
this one does say hello!
this one doesn't
```

If we wanted to output just the lines that had `hello` in them, we would use:

```sh
sed -n "/hello/p" hello2.txt
```

The `-n` flag stops the command from outputing the matched lines twice. The `/p` flag at the end tells us we want to print the matched lines. The output of this command is:

```
hello this is a test file
we like to say hello world when testing code
it is important to say hello when you greet someone
this one does say hello!
```

As we can see, we only output the lines that contain the word `hello`.

I think both commands are fairly easy to use and understand. One drawback I can see if remembering all of the different flags needed to get the desired output. For example, in the first command, if we didn't use the global flag, `g`, we would end up not replacing all of the occurrences, which might be unexpected behavior. For the second command, if we don't include the `-n` flag, all of the matching lines would be printed twice, which might also not be the desired output. While it can be tough to remember these options, I have found `sed` to be very well documented online, so this drawback isn't too bad if you know how to use Google.

**References**

(2012). Linux / Unix: sed Command Print Only Matching Lines. Retrieved from https://www.cyberciti.biz/faq/unix-linux-sed-print-only-matching-lines-command/.

(2019). Sed Command in Linux/Unix with examples. Retrieved from https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/