#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>



#define PERMS 0644

int main(int argc, char *argv[]){
	key_t key=ftok("writer.c",69);
	
	int shmid=shmget(key,1024,PERMS|IPC_CREAT);
	char * shm;
	shm=(char *)shmat(shmid,NULL,0);
	
	char buf[10224];
	while(1){
	sleep(2);
	printf("%s",shm);  // print once and pause till next one gives inou
	
	}
	shmdt(shm);
	
	

	return 0;
}