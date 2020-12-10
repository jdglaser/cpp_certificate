# Discussion Week 12

*Describe how the $* and $@ variables can be used in wordlists and loops. What is a wordlist? What is the purpose of using these variables? Please provide an example using a loop. Describe your example using pseudocode.*

A world list is simply a way to iterate over a string in bash. When we iterate over a string, bash will separate the string by spaces. We can see an example of this below.

```sh
echo "Loop through a word list:"
for word in Hello this is a word list
do
    echo $word
done
```

```
Loop through a word list:
Hello
this
is
a
word
list
```

Additionally we can treat the arguments passed to the shell script as a word list and iterate over those as well:

```sh
echo "Loop through args with \$@:"
for arg in $@
do
    echo $arg
done
```

```
> ./wordlist.sh hello world
Loop through args with $@:
hello
world
```

In the above exmaple, we used `$@` to iterate over the args, however `$*` can be used as well:

```sh
echo "Loop through args with \$*:"
for arg in $*
do
    echo $arg
done
```

```
> ./wordlist.sh hello world
Loop through args with $*:
hello
world
```

When left **unquoted** `$@` and `$*` behave the same. What separates these two variables is their behavior when **quoted**. 

Using a quoted `"$*"` will treat the arguments as one long quoted string:

```sh
echo "Loop through args with \"\$*\":"
for arg in "$*"
do
    echo $arg
done
```

```
> ./wordlist.sh hello world
hello world
```

Using a quoted `"$@"` will treat **each element** as a quoted string:

```sh
echo "Loop through args with \"\$@\":"
for arg in "$@"
do
    echo $arg
done
```

```
> ./wordlist.sh hello world "it's me"
Loop through args with "$@":
hello
world
it's me!
```

**References**

(2014). What's the difference between $@ and $*. Retrieved from https://unix.stackexchange.com/questions/129072/whats-the-difference-between-and.

(2018). Bash Loop Through a List of Strings. Retrieved from https://linuxhint.com/bash_loop_list_strings/.