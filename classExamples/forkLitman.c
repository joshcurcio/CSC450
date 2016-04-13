#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
    /*
    srand(time(NULL));
    int num;
    int i;
    int nums[10];
    for(i = 0; i < 10; i++)
    {
        nums[i] = rand()%2;
        //printf("%d\n", num);
    }
    
    for(i = 0; i < 10; i++)
    {
        printf("woot: %d\n", nums[i]);
    }
    */
    
    printf("About to Fork...\n");
    
    pid_t pid = fork();
    if(pid == 0)
    {
        //I am the child
        int i = 0;
        for(; i < 10; i++)
        {
            printf("Child Count: %d\n", i);
        }
        return 0;
    }
    else
    {
        //I am the parent
        int status;
        waitpid(pid, &status, 0);
        printf("The child is done: %d\n", status);
    }
}