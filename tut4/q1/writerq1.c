#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>


#define PERMS 0666

struct msg_buf{
    long mtype;
    char mtext[200];
    } outgoing;
    
int main(int argc, char argv[]){


	key_t key=ftok("writerq1.c",65);
	int msgid=msgget(key , PERMS|IPC_CREAT);
	
	outgoing.mtype=1;
	sprintf(outgoing.mtext,"SRI JAITRA SAKETH GOPARAJU \n");
	
	msgsnd(msgid,&outgoing,sizeof(outgoing)-sizeof(outgoing.mtype),0);
	
	outgoing.mtype=2;
	sprintf(outgoing.mtext,"2022A7PS0183H \n");
	
	msgsnd(msgid,&outgoing,sizeof(outgoing)-sizeof(outgoing.mtype),0);
	

	return 0;
}