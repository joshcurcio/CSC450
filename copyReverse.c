#include <sys/stat.h>
#include <fcntl.h>
#include "tlpi_hdr.h"
#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
/* Allow "cc -D" to override definition */
 
void main(int argc, char *argv[])
{
    int count;
    char currChar;
    FILE *inputFp, *outputFp;
 
    if (inputFp = fopen(argv[1], "r"))    
    {
        outputFp = fopen(argv[2], "w+");
        count = count_characters(fp1); 
        fseek(inputFp, -1L, 2);
 
        while (count)
        {
            currChar = fgetc(inputFp);
            fputc(currChar, outputFp);
            fseek(inputFp, -2L, 1);
            count--;
        }
    }
}

int count_characters(FILE *f) 
{
    fseek(f, -1L, 2);
    int last_pos = ftell(f);
    last_pos++;
    return last_pos;
}