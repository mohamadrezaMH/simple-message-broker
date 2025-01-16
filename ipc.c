#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <time.h>

#define BUFFER_SIZE 5
#define SHARED_MEMORY_KEY 1234

typedef struct
{
    double data;
    time_t timestamp;
} shared_data;

void producer(shared_data *shared)
{
    for (int i = 0; i < 10; i++)
    {
        while (shared->timestamp != 0)
            ;                                     // wait while data is not consumed
        shared->data = (double)rand() / RAND_MAX; // produce random data
        shared->timestamp = time(NULL);           // record timestamp
        printf("Timestamp: %ld, Value: %.2f\n", shared->timestamp, shared->data);
        sleep(1);
    }
}

void consumer(shared_data *shared)
{
    for (int i = 0; i < 10; i++)
    {
        while (shared->timestamp == 0)
            ; // wait while data is not produced
        printf("Timestamp: %ld, Value: %.2f\n", shared->timestamp, shared->data);
        shared->timestamp = 0; // mark data as consumed
        sleep(1);
    }
}

int main()
{
    int shmid;
    shared_data *shared;

    // Creating shared memory segment
    if ((shmid = shmget(SHARED_MEMORY_KEY, sizeof(shared_data), IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Attaching the shared memory segment
    if ((shared = shmat(shmid, NULL, 0)) == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    shared->timestamp = 0;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        // consumer
        consumer(shared);
    }
    else
    {
        // producer
        producer(shared);
        // Wait for the consumer to finish
        wait(NULL);
        // Detach the shared memory segment
        if (shmdt(shared) == -1)
        {
            perror("shmdt");
            exit(1);
        }
        // Delete the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1)
        {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}