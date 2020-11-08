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
