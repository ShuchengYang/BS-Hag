
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "list.h"
#include <ctype.h>

#define MAX 256

void child_task(int k,char *o_buf);

int main(int argc, char **argv)
{
    int i,k=10,N=1,pid,wstatus,cpid=1,rflag=0,opt;
    list_t *li;
    li=list_init();
    time_t curtime;
    struct list_elem del;
    char o_buf[MAX];
    opterr=0;

    //start time of main process
    time(&curtime);
    printf("Start: %s",ctime(&curtime));

    while((opt=getopt(argc,argv,"k:N:r"))!=-1)
    {
        switch(opt)
        {case 'k': k=atoi(optarg);break;
        case 'N': N=atoi(optarg);break;
        case 'r':rflag=1;break;
        case '?':
        if (optopt == 'k'||optopt=='N')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
        default:abort();
        }
    }
    //generating random k
    if(rflag)
    srand((unsigned)time(0));
    int random_table[N];
    for(i=0;i<N;i++)
    random_table[i]=rand()%(k+1)+0.5*k;
    
    
    for(i=0;i<N;i++)
    {
        time(&curtime);
        if((pid=fork())<0)
        {
            printf("failed to fork a child process.\n");
            exit(1);
        }else if(pid>0)
        {
            list_append(li,&pid);
        }else if(pid==0)
        {
           
            child_task(rflag?random_table[i]:k,o_buf);
           
        }
    }
    while(cpid>0)
     {
        cpid=wait(&wstatus);
        k=WEXITSTATUS(wstatus);
        if(cpid>0){
        sprintf(o_buf,
        "Exit-Code: %i of Process Nr. %i with k=%i\n",(cpid+k)%100,cpid,k);
        write(1,o_buf,strlen(o_buf));}
        //remove terminated child process from process pool
        list_remove(li,&cpid);
     }
   
    list_finit(li);
    //stop time of main process
    time(&curtime);
    printf("Ende: %s",ctime(&curtime));
    return 0;
}

//what those children processes should do
void child_task(int k,char *o_buf)
{
    int i,pid=getpid(),ppid=getppid();
    //you may delete the part below before submit 
    sprintf(o_buf,"k value of p nr. %i is %i\n",pid,k);//not neccessary
    write(1,o_buf,strlen(o_buf));//not naccessary
     //you may delete the part above before submit 
    for(i=1;i<=k;i++)
    {
        sprintf(o_buf,"%i %i %i\n",pid,ppid,i);
        write(1,o_buf,strlen(o_buf));
        sleep(1);
    }
    exit(k);
}
