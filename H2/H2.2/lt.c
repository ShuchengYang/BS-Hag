#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse(const char* instr)
{
    if(strcmp(instr,"-a")==0)
    return 0;
    if(strcmp(instr,"-i")==0)
    return 1;
    if(strcmp(instr,"-r")==0)
    return 2;
    return 3;
}

int main(int argc, char const *argv[])
{ 
    int i;list_t *li;
    li=list_init();
    for(i=1;i<argc;i+=2)
    {
        switch(parse(argv[i]))
        {
            case 0: list_append(li,(char*)argv[i+1]);break;
            case 1: list_insert(li,(char*)argv[i+1]);break;
            case 2: list_remove(li,list_find(li,(char*)argv[i+1],strcmp));break;
            default:
            printf("unrecognized instruction argv loc. %i\n",i);
        }
    }
    list_print(li,print_string);
    list_finit(li);
}