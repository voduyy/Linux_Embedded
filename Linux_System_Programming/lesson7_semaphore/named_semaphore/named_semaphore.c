#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <semaphore.h>

#define POSIX_SEM_NAMED "/named_app"
int main()
{
    sem_t *sem;
    int current_value;
    sem = sem_open(POSIX_SEM_NAMED, O_CREAT | O_EXCL, 0666, 1);
    if (sem == SEM_FAILED)
    {
        if (errno != EEXIST)
        {
            printf("Fail to open semaphore\n");
            exit(EXIT_FAILURE);
        }
        sem_getvalue(sem, &current_value);
        printf("Using old semaphore,current_value is %d\n", current_value);
        sem = sem_open(POSIX_SEM_NAMED, 0);
    }
    // wait
    sem_wait(sem);
    sem_getvalue(sem, &current_value);
    printf("Current_value is %d\n", current_value);

    sem_post(sem);
    sem_getvalue(sem, &current_value);
    printf("Current_value is %d\n", current_value);

    sem_close(sem);

    sem_unlink(POSIX_SEM_NAMED);
}