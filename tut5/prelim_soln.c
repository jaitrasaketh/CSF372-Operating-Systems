#include <sys/ipc.h>
#include<stdio.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


#define PERMS 0644

int main(int argc, char* argv[]){

	key_t key=ftok("prelim_soln.c",65);

	char* shmPtr;
	
	if(fork()==0)
	{// child reads message from shared memory
		int shmid=shmget(key,1024,PERMS|IPC_CREAT);
		shmPtr=(char *)shmat(shmid,NULL,0);
		printf("This is printed in the child process: %s\n",shmPtr);
		shmdt(shmPtr);
		
		
	}
	else{
	  
	    int shmid=shmget(key,1024,PERMS|IPC_CREAT);
		shmPtr=(char *)shmat(shmid,NULL,0);
		
		sprintf(shmPtr,"This is wriiten in the parent process\n");
		
		shmdt(shmPtr);
		
		shmctl(shmid,IPC_RMID,0);
	 
	
	
	
	
	}





	return 0;
}