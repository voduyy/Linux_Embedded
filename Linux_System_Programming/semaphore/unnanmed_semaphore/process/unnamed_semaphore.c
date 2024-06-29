#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>

int main()
{
    char *p = (char *)mmap(0, 1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *p = 65;
    sem_t *semaphore, *semaphore2;
    semaphore = (sem_t *)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    semaphore2 = (sem_t *)mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_init(semaphore, 1, 1);
    sem_init(semaphore2, 1, 1);
    pid_t child_pid = fork();
    if (child_pid == 0)
    {
        printf("Im child process \n");
        sem_wait(semaphore);
        sem_wait(semaphore2);
        ++(*p);
        printf("Child: %d\n", *p);
        sem_post(semaphore2);
        munmap(p, 1);
        munmap(semaphore, sizeof(semaphore));
        munmap(semaphore2, sizeof(semaphore2));
    }
    else
    {
        printf("Im parent process \n");
        sem_wait(semaphore2);
        --(*p);
        printf("Parent: %d\n", *p);
        sem_post(semaphore);
        sem_post(semaphore2);
        // chi co parent moi co the unlink semaphore
        sem_destroy(semaphore);
        sem_destroy(semaphore2);
        munmap(p, 1);
        munmap(semaphore, sizeof(semaphore));
        munmap(semaphore2, sizeof(semaphore2));
    }
}