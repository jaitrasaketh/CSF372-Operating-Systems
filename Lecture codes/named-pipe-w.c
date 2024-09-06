#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
   int fd;
   char myfifo_path[20]="/tmp/myfifo_path"; // tmp is a directory in Linux that stores temporary files and overtime it gets cleared
   mkfifo(myfifo_path,0666); // make fifo by sending the path and permissionsss 0110==> read and write permissions to owner,group and others
   fd=open(myfifo_path,O_WRONLY);  // open a file descriptor that writes only
   write(fd,"Hello World!", strlen("Hello World!")+1);   // +1 to take that /0 character as well
   close(fd);
   }
