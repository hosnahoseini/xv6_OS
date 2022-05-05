#include "types.h"
#include "stat.h"
#include "user.h"

#define PAGESIZE 4096

int thread_creator(void (*fn) (void *), void *arg, int status){
    //alocating 2* pagesize for fptr in heap
    void *fptr = malloc(2 * PAGESIZE);
    void *stack;
    if(fptr == 0)
        return -1;
    //check if it is page aligned
    int mod = (uint) fptr % PAGESIZE;

    if(mod == 0) //if it is page aligned
        stack = fptr;
    else //if it's not
        stack = fptr + (PAGESIZE - mod);
    
    int thread_id = thread_create((void *)stack, status);

    if(thread_id < 0)   
        printf(1, "thread create failed\n");
    else if (thread_id == 0){
        //child
        (fn)(arg); //call the function passed to thread_create
        free(stack); //free space when function is finished
        exit();
    }
    return thread_id;
}
