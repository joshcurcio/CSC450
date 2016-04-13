#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
    int filedes[1];
    pipe(filedes);
    
    char* buf = "hello";
    char* buf2 = malloc(5 *sizeof(char));
        
    write(filedes[1], buf, 5);
    
    int pid = fork();
    
    if (pid == 0)
    {
        read(filedes[0], buf2, 5);
        printf("%s\n", buf2); 
        write(filedes[1], "woot", 4);
    }
    else
    {
        printf("hi im the parent\n"); 
        int numRead = 0;
        while(numRead == 0)
        {
            numRead = read(filedes[0], buf2, 5);
        }
        printf("%s\n", buf2);
    }
    
   
    
    
    return 0;
}