#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "tictactoe.h"
#define SHMSZ 9

int main(int argc, char * * argv)
{
    srand(time(NULL));
    char c;
    int shmid;
    int randomBucket = 0;
    key_t key;
    char * shm, * s;
    int status;

    /*
     * We'll name our shared memory segment
     * "5678".
     */
    key = 5678;

    /*
     * Create the segment.
     */
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        return -1;
    }

    /*
     * Now we attach the segment to our data space.
     */
    if ((shm = shmat(shmid, NULL, 0)) == (char * ) - 1)
    {
        perror("shmat");
        return -1;
    }

    int i = 0;

    for (i; i < 9; i++)
    {
        shm[i] = ' ';
    }

    shm[9] = 'p';

    int pid = fork();

    if (pid != 0)
    {
        while (1 == 1)
        {

            if (shm[9] == 'p')
            {
                //critical section
                //parent goes
                //critical section
                randomBucket = rand() % 9;
                while (shm[randomBucket] != ' ')
                {
                    randomBucket = rand() % 9;
                }
                shm[randomBucket] = 'x';

                int won = checkWin('x', shm);
                if (won == 1) //winner
                {
                    printf("%c | %c | %c\n", shm[0], shm[1], shm[2]);
                    printf("---------\n");
                    printf("%c | %c | %c\n", shm[3], shm[4], shm[5]);
                    printf("---------\n");
                    printf("%c | %c | %c\n", shm[6], shm[7], shm[8]);
                    printf("Parent: winner\n");
                    shm[9] = 'w';
                    break;
                }
                else if (won == 2) //tie
                {
                    printf("%c | %c | %c\n", shm[0], shm[1], shm[2]);
                    printf("---------\n");
                    printf("%c | %c | %c\n", shm[3], shm[4], shm[5]);
                    printf("---------\n");
                    printf("%c | %c | %c\n", shm[6], shm[7], shm[8]);
                    printf("Parent: tie\n");
                    shm[9] = 'w';
                    break;
                }
                else
                {
                    shm[9] = 'c';
                }
            }
            else if (shm[9] == 'w')
            {
                exit(0);
            }
            waitWhileEqual('c', shm);
        }
    }
    else
    {
        while (1 == 1)
        {
            if (shm[9] == 'c')
            { //critical section
                //child goes
                randomBucket = rand() % 9;
                while (shm[randomBucket] != ' ')
                {
                    randomBucket = rand() % 9;
                }
                shm[randomBucket] = 'o';

                int won = checkWin('o', shm);
                if (won == 1) //winner
                {
                    printf("%c | %c | %c\n", shm[0], shm[1], shm[2]);
                    printf("-------------\n");
                    printf("%c | %c | %c\n", shm[3], shm[4], shm[5]);
                    printf("-------------\n");
                    printf("%c | %c | %c\n", shm[6], shm[7], shm[8]);
                    printf("Child: winner\n");
                    shm[9] = 'w';
                    break;
                }
                else if (won == 2) //tie
                {
                    printf("%c | %c | %c\n", shm[0], shm[1], shm[2]);
                    printf("-------------\n");
                    printf("%c | %c | %c\n", shm[3], shm[4], shm[5]);
                    printf("-------------\n");
                    printf("%c | %c | %c\n", shm[6], shm[7], shm[8]);
                    printf("Child: tie\n");
                    shm[9] = 'w';
                    break;
                }
                else
                {
                    shm[9] = 'p';
                }
            }
            else if (shm[9] == 'w')
            {
                exit(0);
            }
            waitWhileEqual('p', shm);
        }

    }
}

int checkWin(char c, char * shm)
{
    if ((((shm[0] == shm[1]) && (shm[0] == shm[2])) && (shm[0] == c)) ||
        (((shm[3] == shm[4]) && (shm[3] == shm[5])) && (shm[3] == c)) ||
        (((shm[6] == shm[7]) && (shm[6] == shm[8])) && (shm[6] == c)) ||
        (((shm[0] == shm[3]) && (shm[0] == shm[6])) && (shm[0] == c)) ||
        (((shm[1] == shm[4]) && (shm[1] == shm[7])) && (shm[1] == c)) ||
        (((shm[2] == shm[5]) && (shm[2] == shm[8])) && (shm[2] == c)) ||
        (((shm[0] == shm[4]) && (shm[0] == shm[8])) && (shm[0] == c)) ||
        (((shm[6] == shm[4]) && (shm[6] == shm[2])) && (shm[6] == c)))
    {
        return 1; //winner
    }
    else if (shm[0] != ' ' &&
        shm[1] != ' ' &&
        shm[2] != ' ' &&
        shm[3] != ' ' &&
        shm[4] != ' ' &&
        shm[5] != ' ' &&
        shm[6] != ' ' &&
        shm[7] != ' ' &&
        shm[8] != ' ')
    {
        return 2; //tie
    }
    return 0;
}

void waitWhileEqual(char val, char * shm)
{
    while (shm[9] == val)
    {
        //wait
    }
}