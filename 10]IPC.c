#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SEGSIZE 100

int main(int argc, char *argv[]) {
    int shmid;
    key_t key;
    char *segptr;
    char buff[] = "poooda";

    // Step 1: Generate a unique key for the shared memory segment
    key = ftok(".", 's');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Step 2: Try to create the shared memory segment
    if ((shmid = shmget(key, SEGSIZE, IPC_CREAT | IPC_EXCL | 0666)) == -1) {
        // If the segment already exists, get it
        if ((shmid = shmget(key, SEGSIZE, 0)) == -1) {
            perror("shmget");
            exit(1);
        }
    } else {
        printf("Creating a new shared memory segment\n");
        printf("SHMID: %d\n", shmid);
    }

    // Step 3: Display shared memory segments
    system("ipcs -m");

    // Step 4: Attach the shared memory segment to the process's address space
    if ((segptr = (char *)shmat(shmid, 0, 0)) == (char *)-1) {
        perror("shmat");
        exit(1);
    }

    // Step 5: Write data to the shared memory
    printf("Writing data to shared memory...\n");
    strcpy(segptr, buff);
    printf("DONE\n");

    // Step 6: Read data from the shared memory
    printf("Reading data from shared memory...\n");
    printf("DATA: %s\n", segptr);
    printf("DONE\n");

    // Step 7: Remove the shared memory segment
    printf("Removing shared memory segment...\n");
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        printf("Can't remove shared memory segment...\n");
    } else {
        printf("Removed successfully\n");
    }

    return 0;
}
