#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include<sys/ipc.h>
#include <sys/wait.h>


#define PERMS 0644

int main(int argc, char *argv[]){
	int *shm;
	int shmid=shmget(IPC_PRIVATE,1024,PERMS|IPC_CREAT);
	if(fork()!=0){
		
		shm=(int *)shmat(shmid,NULL,0);
		*shm=getpid();
		wait(NULL);
		
		shmdt(shm);
		}
	else
	{
		
		shm=(int *)shmat(shmid,NULL,0);
		
		sleep(1);
		printf("The pid of the parent process that's being printed in the child process is : %d\n",*shm);
		
		shmdt(shm);
		}
		
		
	return 0;
}