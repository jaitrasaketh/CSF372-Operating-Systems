#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define PERMS 0644 ;// PERMISSIONS :read and write for owner, read only for the rest


struct my_msgbuf
{
   long mtype;
   char mtext[200];
   }; // one unit of the message queue



int main(int argc, char const *argv[])
{
  struct my_msgbuf buf;
  int msqid,len;
  key_t key;
      if((key== ftok("msgq-w.c","B"))==-1)
      {
	      perror("Error in ftok() \n");
	      exit(-1);
      }
      
      
      if(msqid==msgget(key,PERMS|IPC_CREAT))==-1)
      {
	      perror("Error in msgget()\n");
	      exit(-2);
      }
      
      buf.mtype=1;
      sprintf(buf.mtext,"%s","Hi");
      len=strlen(buf.mtext);
      
      if(msgsnd(msqid,&buf,len+1,0))==-1)
      {
	      perror("Error in msgsnd() \n");
	      exit(-3);
      }
      
      
      
 return 0;
    
  
  
}
