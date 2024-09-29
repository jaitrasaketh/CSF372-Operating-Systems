#include <stdio.h>
#include <stdlib.h>
#include<sys/ipc.h>
#include <sys/types.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include <string.h>

struct msg_buffer{

    long mtype;
    int key_or_freq;
};

char *decoded(char* word, int key){
    int i=0;
    while(word[i]!='\0'){
        if(word[i]>= 'a'&& word[i]<= 'z')
        {
            word[i]=(word[i]-'a'+key )%26+'a';
        }
        i++;
    }

    return word;
} /// decode the string - Caeser cipher logic

int noOfOccurrences(char*word, char* words_buffer){ 

    int count=0; char*pos= words_buffer;// points at the start position of the buffer
    int word_len=strlen(word);
    while((pos=strstr(pos,word))!=NULL)
    {
        if((pos==words_buffer||*(pos-1)== ' ') &&(*(pos+word_len) ==' ')||*(pos+word_len) == '\0') // check for no substring
        {
            count++;
        }
        pos+=word_len;


    }
    return count;
}


int main(int argc, char *argv[]) {
    FILE *input_file;
    int N;
    int stringSize;
    int key_sm;
    int key_mq;// contents of input file
    char line_reader[200]; // pointer to the buffer that would read the input.txt file

    
    char input_filename[20]; // pointer to the buffer that would store the output(name of the file)
    sprintf(input_filename , "input%s.txt",argv[1]);

    input_file=fopen(input_filename, "r");

    if (input_file== NULL) {
        perror("Wasn't able to open the requested file for some reason ");
        exit(-1);
    }
        if(fgets(line_reader, sizeof(line_reader) ,input_file))
            N = atoi(line_reader);
        else
        {
            perror("Error in line 1");
            exit(-1);
        }
        if(fgets(line_reader,sizeof(line_reader),input_file))
            stringSize= atoi(line_reader);
            else{
                perror("Error in line 2");
                exit(-1);
            }
        if(fgets(line_reader,sizeof(line_reader),  input_file))
            key_sm = atoi(line_reader);
            else{
                perror("Error in line 3");
                exit(-1);
            }
        if(fgets(line_reader, sizeof(line_reader), input_file))
            key_mq = atoi(line_reader); 
            else{
                perror("Error in line 4 ");
                exit(-1);
            }
    

   
   
    fclose(input_file);

//input{t}.txt is read and useful information is extracted
    

    FILE * words_file;
    char words_filename[20];
    sprintf(words_filename,"words%s.txt",argv[1]);

    words_file=fopen(words_filename,"r");
    if(words_file==NULL){
        perror("The words file isnt opening for some reason");
        exit(-2);
    }
   // input the words{t}.txt

   fseek(words_file,0 ,SEEK_END);
   int file_size_in_bytes=ftell(words_file );
   rewind(words_file);

   char *words_buffer=(char*)malloc( file_size_in_bytes+1); //  +1 to accomodate for '\0' character
   
   size_t size_of_each_element=1;
   fread(words_buffer,size_of_each_element,file_size_in_bytes,words_file);
   fclose(words_file );

   words_buffer[file_size_in_bytes]='\0'; // last character of the words buffer is \0

   //shifted the words in the file into a buffer into memory to read repeatedly for every iteration

   /*
       updations made in the noOfOccurrences function and its function calls

       --> new updations crossing limit
       min_word_length = 1
       max_word_length = 100
       n = 250
       word_count = 100000   time 25sec

       _______________________
         
        min_word_length = 1
       max_word_length = 4095
       n = 50
       word_count = 10000  time 25sec

       attempt for optimization usign threads
       
    */

    int shmid= shmget(key_sm, N* N* stringSize, 0666| IPC_CREAT);
    if (shmid == -1) 
    {
        perror("shared memory not accessible ");
        exit(-1);
    }
    
    char (*shmptr)[N][stringSize] = shmat(shmid, NULL, 0);

   /*now logic
   1.solve no of occurrences of first string in the words.txt
   2.send answer in the outgoing
   3.receive caeser key from the incoming. if answer in  step 2 is incorrect send -1 and exit
   4.decode the new string with the caeser key
   5. repeat this until the right diagonals are over
   6. Once this is done it returns--> 0 if right and -1 if wrong
   */
  
  int msgid;
  struct msg_buffer incoming,outgoing;
  if((msgid= msgget(key_mq,0666|IPC_CREAT )) ==-1){
    perror("message Queue not found ");
    exit(-1);
  } 
  
  outgoing.mtype=1; // helper recceives mtype 1
  incoming.mtype=2; // helper sends with mtype 2

  int d=0;
  while(d<2*N-1){
    int sum_right_diagonal_occurrences=0;
    int nOccur;
    for(int i=0;i<N;i++)
    {   
        int j=d-i;
        if(j>=0&& j<N){  
        if(d>0){
                nOccur=noOfOccurrences(decoded(shmptr[i][j], incoming.key_or_freq),words_buffer  );
                }
                else
                 {nOccur=noOfOccurrences( shmptr[i][j],words_buffer ) ;}
                 sum_right_diagonal_occurrences+=nOccur;
               
       
        
        
    }}
  
   outgoing.key_or_freq = sum_right_diagonal_occurrences;

  if(msgsnd(msgid, &outgoing,sizeof(outgoing) -sizeof(outgoing.mtype),0)== -1)
  {
    perror("sum of No of occurrences not sent");
    exit(-1);
  }



  if(msgrcv(msgid,&incoming ,sizeof(incoming)- sizeof(incoming.mtype),2,0) == -1)
  {
    perror("Error in receiving the key");
    exit(-1);
  }
  
  if(incoming.key_or_freq==-1){
    perror("incorrect");
    exit(-1);

  }
  if(d==2*N-2&& incoming.key_or_freq==0)
  {
     break;
  }

  d++;
}

shmdt(shmptr);

return 0;

}





// optimisation of no of Occurrences fucntion, reduce reading the file so many times
   

/*
N=250   max word_count=1000 (3) limit
N=20    word_count=100000 (5)  
N=100   word_count=10000
*/




