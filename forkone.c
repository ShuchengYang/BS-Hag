#include <stdlib.h>
#include  <stdio.h>
#include  <string.h>
#include  <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    char o_buf[MAX_B];
    int counter;
    int wstatus;
    time_t curtime;

//  time
time(&curtime);
printf("Start: %s",ctime(&curtime));
    if((pid=fork())<0)
    {
        printf("failed to fork a child process\n");
        exit(1);
    } else if(pid==0)
    {
        int k=atoi(argv[1]);
        for(counter=1;counter<=k;counter++)
        {
            sprintf(o_buf,"%i %i %i\n",getpid(),getppid(),counter);
            write(1,o_buf,strlen(o_buf));
            sleep(1);
        }
        exit((getpid()+k)%100);
    }

    pid=wait(&wstatus);
    printf("Exit-Code: %i\n",WEXITSTATUS(wstatus));
    //time
    time(&curtime);
    printf("Ende: %s",ctime(&curtime));
    exit(0);
}

