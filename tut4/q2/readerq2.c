#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>


#define PERMS 0666

struct msg_buf{
	long mtype;
	char mtext[200];
	}incoming;
	
	
int main(int argc, char argv[]){

	key_t key=ftok("writerq2.c",65);
	
	int msgid=msgget(key, PERMS|IPC_CREAT);
	
	msgrcv(msgid,&incoming,sizeof(incoming)-sizeof(incoming.mtype),3,0);
	printf("%s\n",incoming.mtext);
	
	msgrcv(msgid,&incoming,sizeof(incoming)-sizeof(incoming.mtype),2,0);
	printf("%s\n",incoming.mtext);
	
	
	msgrcv(msgid,&incoming,sizeof(incoming)-sizeof(incoming.mtype),1,0);
	printf("%s\n",incoming.mtext);
	
	
	
	
	
	msgctl(msgid,IPC_RMID,NULL);

	return 0;
}