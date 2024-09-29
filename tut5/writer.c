#include <sys/ipc.h>
#include<sys/shm.h>
#include <stdio.h>
#include<stdlib.h>


#define PERMS 0644

int main(int argc, char * argv[]){
	
	key_t key=ftok("writer.c",69);
	char * shm;
	
	int shmid=shmget(key,1024,PERMS|IPC_CREAT);
	shm=(char *)shmat(shmid,NULL,0);
	while(1){
		fgets(shm,1024,stdin);
		
	}
	
	
	shmdt(shm);
	
	
	return 0;	
}