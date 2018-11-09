#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <errors.h>
#include "list.h"

static int print_counter;

list_t  *list_init ()
{
    static list_t *listbuffer;
    listbuffer= (list_t *)malloc(sizeof(list_t)); 
    if(listbuffer==NULL)//errot handeling
    {
        // perror("failed to creat a simple linked list");
        printf("failed to creat a simple linked list\n"); 
        return NULL;
    }
    listbuffer->first=NULL;
    listbuffer->last=NULL;
    return listbuffer;
}

struct list_elem *list_insert (list_t *list, int *data)
{
    static struct list_elem *element;
    element=(struct list_elem *)malloc(sizeof(struct list_elem));
    if(element==NULL) //error handeling
    {
        // perror("failed to instert element into list");
        printf("failed to insert element into list\n");
        return NULL;
    }
    element->next=list->first;
    element->data=data;
    list->first=element;
    if(element->next==NULL)
    list->last=element;
    return element;
}

struct list_elem *list_append (list_t *list, int *data)
{
    static struct list_elem *element;
    element=(struct list_elem *)malloc(sizeof(struct list_elem));
    if(element==NULL) //error handeling
    {
        // perror("failed to append element to list end");
        printf("failed to append element to list end\n");
        return NULL;
    }
    element->next=NULL;
    element->data=data;
    if(list->first==NULL)
    list->first=element;
    if(list->last!=NULL)
    list->last->next=element;
    list->last=element;
    return element;
}


int list_remove (list_t *list, int *data)
{
    int jump_flag=0;
    if(list->first==NULL)
    return -1;
    struct list_elem *search,*presearch;
    search=list->first;
    presearch=NULL;
    
    while(search!=NULL)
    {
        if(*(search->data)==*(data))
        {
            if(search==list->first)
            {
                list->first=search->next;
                jump_flag=1;
            }
            if(search==list->last)
            {
                list->last=presearch;
                if(presearch!=NULL)
                presearch->next=NULL;
                jump_flag=1;
            }
            if(jump_flag!=1)
            presearch->next=search->next;
            free(search);
            return 0;
        }
        presearch=search;
        search=search->next;
    }
    
    return -1;
}

void list_finit (list_t *list)
{
    if(list->first!=NULL)
    {
        struct list_elem *delelem=list->first,*predel=NULL;
        while(delelem!=NULL)
        {
            predel=delelem;
            delelem=delelem->next;
            free(predel);
        }
    }
    free(list);
}

void list_print (list_t *list, void (*print_elem) (int *))
{
    struct list_elem *traverse=list->first;
    print_counter=1;
    while(traverse!=NULL)
    {
        print_elem(traverse->data);
        traverse=traverse->next;
    }
}

struct list_elem *list_find (list_t *list, int *data)
{
    struct list_elem *search=list->first;
    while(search!=NULL)
    {
        if(*(search->data)==*data)
        break;
        // {printf("element %s found\n",data);break;}//
        search=search->next;
    }
    if(search==NULL)
    return NULL;
    // {printf("element %s not found!",data);return NULL;}//
    static struct list_elem *result;
    result=search;
    // printf("element %s will be return\n",result->data);//
    return result;
}

void print_int(int *data)
{
    printf("%i:%i\n",print_counter,*data);
    print_counter++;
}

