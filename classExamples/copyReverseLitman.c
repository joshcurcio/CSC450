#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#ifndef BUF_SIZE
#define BUF_SIZE 1
#endif
/* Allow "cc -D" to override definition */


int main(int argc, char *argv[])
{
  int numBytes = getNumBytes(argv[1]);
  int outputFd, openFlags; mode_t filePerms;
  openFlags = O_CREAT | O_WRONLY | O_TRUNC;
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; /* rw-rw-rw- */
  outputFd = open(argv[2], openFlags, filePerms);
  int i = numBytes;
  char answer[1];
  
  for(; i > 0; i--)
  {
    answer[0] = getCharAtIndex(i, argv[1]);
    write(outputFd, answer, BUF_SIZE);
    //printf("%c", getCharAtIndex(i, argv[1]));
  }
  close(outputFd);
  exit(EXIT_SUCCESS);
}

int getCharAtIndex(int index, char* fn)
{
  int inputFd = open(fn, O_RDONLY);
  ssize_t numRead;
  char buf[BUF_SIZE];
  int i = 0;
  for(; i < index; i++)
  {
    read(inputFd, buf, BUF_SIZE);
  }
  close(inputFd);
  return buf[0]; //buf
}

int getNumBytes(char* fn)
{
  int inputFd = open(fn, O_RDONLY);
  ssize_t numRead;
  int numBytes = 0;
  char buf[BUF_SIZE];
  while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
  {
    numBytes++;
  }
  close(inputFd);
  return numBytes;
}