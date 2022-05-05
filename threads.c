//threads.c is for testing
#include "types.h"
#include "stat.h"
#include "user.h"
int x = 0;
int stack[4096] __attribute__ ((aligned (4096)));

int main(int argc, char *argv[]){
    //pass stack to thread create in order to allocate memory
    int tid = thread_create(stack);
    if(tid < 0){
        printf(2, "error\n");
    }else if(tid == 0){
        //child is born
        for(;;){
            x++;  //increase x( as much as number of children )
            sleep(100);
        }
    } else{
        //parent
        for(;;){
            printf(1, "x = %d\n", x); //parent prints value of x (shared memory with children)
            sleep(100);
        }
    }
    exit();
}
