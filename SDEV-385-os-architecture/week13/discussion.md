# Discussion Week 13

Based on your reading, the lecture, lab and some of the references listed in the lecture, answer the following questions:

*What are some of the unique features of an enhanced security operating system?*

Security Enhanced Linux adds additional security features to Linux that make it more secure to hackers and malware authors. Some unique features that make security enhanced Linux more secure include:
- Ability to control access on more variables such as which users or applications can access certain resources
- Standard Linux access controls (-rwxr-xr-x) are not modifiable by th eindividual user or user programs, but instead are controlled by policies that are loaded onto the system.
- Finer granularity to access controls.  Instead of just read, write, or execute you can also specify who can unlink, append, move a file, etc.
- Access to other resources such as network resources can be controlled

*How will OS configuration affect code that you may have to write?*

This depends heavily on the OS configuration and the OS being used. If Linux is configured with SELinux, then we have to be aware of security policies when accessing files, storage, network resources, etc. Unlike some of the programs we have written in this class, simple system calls to check and change the permissions of a file or directory may not be allowed and would have to be accounted for.

*What will you have to take into consideration if you need to recompile the operating system?*

You would have to take into considerations exisitng security policies in place. If recompiling a system already configured with SE Linux, you would want to make sure these configurations carried over. If recompiling a system to be compatible with SE Linux, you would need to understand exactly what security policies you want to enforce and for which groups of users.

*What did you learn about the Battleship source code from this week's lab to understand how Jif implements policies?*

I found the Jif language to be really interesting. It is an extension on Java which allows greater access control over information using security policy annotations. For example:

```java
int {Alice→Bob} x;
int {Alice→Bob, Chuck} y;
x = y; // OK: policy on x is stronger
y = x; // BAD: policy on y is not as strong as x
```

In the above snippet, principal Alice permits information in variable x to be seen by principal Bob. Principal Alice then allows information in y to be viewed by both Bob and Chuck. The first statement is okay, because Bob is allowed to see x and y. However, the second will result in an error at compile time because Chuck is not allowed to see information in Y.

Jif ensures our programs safely transfer information without unauthorized principals gaining access.

The Battelship source code is a good example of how Jif might be used. We know Battelship is a two player game where eahc player can see their own board, but not the other's. This creates a perfect use case for creating policies in code where each player can only see specific information in the game.

**References**

(2020). Week 13: Lecture - Linux Security [Lecture Notes]. Retrieved from https://champlain.instructure.com/courses/1414532/pages/week-13-lecture-linux-security?module_item_id=62587571

(2020). SELinux Project Wiki. Retrieved from http://www.selinuxproject.org/page/Main_Page.

(2020). Jif Reference Manual - Introduction. Retrieved from http://www.cs.cornell.edu/jif/.

