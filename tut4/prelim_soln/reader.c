#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define PERMS 0666 // read and write for everyone

struct msg_buf{
    long mtype;
    char mtext[200];
} incoming;

int main(int argc, char * argv[]){
  
    key_t key=ftok("writer.c",65);
    int msgid=msgget(key, PERMS|IPC_CREAT);
    
    msgrcv(msgid,&incoming,sizeof(incoming)-sizeof(incoming.mtype),1,0);
    
    
    printf("%s",incoming.mtext);
    
    

  return 0;
}
