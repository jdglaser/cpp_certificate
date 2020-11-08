# Discussion Week 10

**Program 1**

```c
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    mode_t theMode;
    char theType[100];
    char *theFileName;
    int theFileDescriptor;
    struct stat theBuffer;

    theFileName = argv[1]; //Save the file name

    //Open the file, throw an error if open fails
    if ((theFileDescriptor = open(theFileName, O_RDONLY)) < 0)
    {
        perror("Fail on Open");
        exit(EXIT_FAILURE);
    }

    //Grab the file statistics
    if ((fstat(theFileDescriptor, &theBuffer)) < 0)
    {
        perror("Unable to get Statistics");
        exit(EXIT_FAILURE);
    }

    theMode = theBuffer.st_mode;

    printf("The File: %s\n", theFileName);
    printf("The Size: %ld\n", theBuffer.st_size);
    printf("The block size: %ld\n", theBuffer.st_blksize);
    //printf("The Device: %i\n", major(theBuffer.st_dev), minor(theBuffer.st_dev));
    printf("The Mode: %#o\n", theMode & ~(S_IFMT));
    printf("The UID: %d\n", theBuffer.st_uid);
    printf("The group ID: %#o\n", theBuffer.st_gid);

    //Close the file
    if (close(theFileDescriptor) < 0)
    {
        perror("Fail on Close");
    }

    return 0;
}
```

I could not get the `major` and `minor` themes to work. I kept getting the error:

```
warning: implicit declaration of function ‘minor’
warning: implicit declaration of function ‘major’
```

However, I was able to add some additional information with:
- Group ID
- Block size

**Second Program**

```c
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

// Generalized error handling function
int handleError(int res) {
  if (res < 0) {
    perror(strerror(errno));
    exit(EXIT_FAILURE);
  }
  return res;
}

int main (int arc, char **argv) {
  char *inputFileName;//Will need full path if not in same directory as the exe!
  char *outputFileName;
  int count;
  int inputFileDescriptor;
  int outputFileDescriptor;
  struct stat theStatus;

  inputFileName = argv[1];
  outputFileName = argv[2];

  // Open the input file
  inputFileDescriptor = handleError(open(inputFileName,O_RDONLY));//Read only
  outputFileDescriptor = handleError(open(outputFileName,O_RDWR | O_CREAT, S_IRWXU));

  // Truncate the output file
  handleError(ftruncate(outputFileDescriptor, 0));

  // Grab the file statistics
  handleError(fstat(inputFileDescriptor, &theStatus));

  // Get file size in bytes
  off_t fileSize = theStatus.st_size;

  // Set the buffer size and create the buffer
  int BUFFER_SIZE = 10;
  char buffer[BUFFER_SIZE];

  // Start at beginning of file
  lseek(inputFileDescriptor,0,SEEK_SET);

  // Initially read as many bytes as possible into the buffer
  ssize_t bytesRead = handleError(read(inputFileDescriptor, buffer, BUFFER_SIZE));
  // Set number to track bytes written
  ssize_t totalBytesWritten = 0;
  while (bytesRead > 0) {
    ssize_t bytesWritten = handleError(write(outputFileDescriptor, buffer, bytesRead));
    bytesRead = handleError(read(inputFileDescriptor, buffer, BUFFER_SIZE));
    totalBytesWritten += bytesWritten;
    printf("%ld/%ld bytes written\n", totalBytesWritten, fileSize);
  }

  handleError(close(inputFileDescriptor));
  handleError(close(outputFileDescriptor));

  return 0;
}
```

Some notes about changes I made to this lab:

- Added a generalized error handling helper function
- Changed the `for` loop to a `while` loop - the `read` function returns the number of bytes read, so we can use this as an exit condition
- Used the file size from `stats` to g=output the total bytes every time bytes are written to the new file.
- Decreased the buffer size so we can see the `read` and `write` functions in action more clearly.
- Added `ftruncate` function to clear the output file at the start of the program
- Added flags `O_CREAT` and `S_IRWXU` in the `open` function call for the output file. This allows the program to create the file if it does not exist, and also automatically gives read, write, and execute permissions to the user who is running the program.

An example run with the following test file can be seen below:

**inputFile.txt**:

```
Anim aute consectetur esse quis reprehenderit Lorem dolore nisi commodo ex. 
Non dolor nisi veniam reprehenderit laboris. 
Minim cillum magna aute dolore aliquip eiusmod cupidatat exercitation tempor.
Id elit pariatur sunt nisi occaecat.
```

**Output**:

```
10/237 bytes written
20/237 bytes written
30/237 bytes written
40/237 bytes written
50/237 bytes written
60/237 bytes written
70/237 bytes written
80/237 bytes written
90/237 bytes written
100/237 bytes written
110/237 bytes written
120/237 bytes written
130/237 bytes written
140/237 bytes written
150/237 bytes written
160/237 bytes written
170/237 bytes written
180/237 bytes written
190/237 bytes written
200/237 bytes written
210/237 bytes written
220/237 bytes written
230/237 bytes written
237/237 bytes written
```

**References**

https://man7.org/linux/man-pages/man2/open.2.html
https://man7.org/linux/man-pages//man2/read.2.html
https://www.man7.org/linux/man-pages/man2/write.2.html