#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define PERMS 0644
#define SHM_SIZE 4096 * 2

int main(int argc, char *argv[]) {
    pid_t first, second;
    key_t key = ftok("take_home.c", 65);
    char *shm;

    int shmid = shmget(key, SHM_SIZE, PERMS | IPC_CREAT);
    shm = (char *)shmat(shmid, NULL, 0);
    
    char *shmPtr1 = shm; // Pointer for first child's data
    char *shmPtr2 = shm + SHM_SIZE / 2; // Pointer for second child's data

    if ((first = fork()) == 0) {  // First child reads from the first file
        FILE *file1 = fopen(argv[1], "r");
        char c;
        while ((c = fgetc(file1)) != EOF) {
            *shmPtr1 = c;
            shmPtr1++;
        }
        *shmPtr1 = '\0';  // Null-terminate to indicate end of data
        fclose(file1);
        shmdt(shm);  // Detach shared memory
        return 0;
    }

    wait(NULL); 

    if ((second = fork()) == 0) {  // Second child reads from the second file
        FILE *file2 = fopen(argv[2], "r");
        char c;
        while ((c = fgetc(file2)) != EOF) {
            *shmPtr2 = c;
            shmPtr2++;
        }
        *shmPtr2 = '\0';  // Null-terminate to indicate end of data
        fclose(file2);
        shmdt(shm);  // Detach shared memory
        return 0;
    }

    wait(NULL);  // Wait for second child to finish

    // Parent process writes to the third file
    FILE *file3 = fopen(argv[3], "w");
   
    // Write first child's data
    shmPtr1 = shm; // point to the start character of the shared memory
    while (*shmPtr1 != '\0') {
        fputc(*shmPtr1, file3);
        shmPtr1++;
    }

    // Write second child's data
    shmPtr2 = shm + SHM_SIZE / 2; // point to the start of the second child's data
    while (*shmPtr2 != '\0') {
        fputc(*shmPtr2, file3);
        shmPtr2++;
    }

    fclose(file3);
    shmdt(shm);  // Detach shared memory
    shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory segment

    return 0;
}