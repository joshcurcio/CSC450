#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

main(int argc, char** argv)
{
    char c;
    int shmid;
    key_t key;
    char *shm, *s;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        return -1;
    }
    
     /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    
    c = 'a';
    int i;
    for (i = 0; c <= 'z'; c++ , i++)
    {
        shm[i] = c;
    }
    shm[26] = '?';
    int pid = fork();
    if(pid!=0)
    {
        //parent
        while(smh[26] == '?')
        {
            //wait
        }
        printf("parent: %c\n", shm[26]);
    }
    else
    {
        printf("child %c", shm[26]);
        shm[26] = 'x';
        printf("child %c", shm[26]);
    }
    
    return 0;
}