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
