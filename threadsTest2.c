#include "types.h"
#include "stat.h"
#include "user.h"

void childPrint(void *args){
    // printf(1, "hi, childs function executed properly with argument: %d\n", *(int *) args);
    printf(1, "===========================\n");
    printf(1, "***************************\n");

    return;
}
int main(void){
    int argument = 0x0F01;
    int thread_id = thread_creator(&childPrint, (void *)&argument);
    printf(1, "child pid = %d \n", thread_id);
    if(thread_id < 0){
        printf(1, "thread_creator failed\n");
    }else{
        if(thread_id > 0){
            int c = thread_join(5);
            printf(1, "%d\n" , c);
            printf(1, "thread_id is: %d\n", thread_id);
        }
    }


    exit();
}