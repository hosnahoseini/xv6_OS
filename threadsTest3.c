#include "types.h"
#include "stat.h"
#include "user.h"

void function(void *args){
    base ++;
    if(base >= limit){
        exit();
    }else{
        int thread_id = thread_creator(&function, (void *)&argument);
        int result = thread_join(thread_id);
        printf("Base = %d, Limit = %d\n", base, limit);

        if(result == -1)
            printf("[ID] %d => [Failed] -1\n", thread_id);
        else
            printf("[ID] %d => [Success] 0\n", thread_id);
    }

}

int base, limit;
int main(void){
    int argument = 0x0F01;
    int thread_id = thread_creator(&childPrint, (void *)&argument);
    printf("Done! \nBase = %d, Limit = %d", base, limit);

    exit();
}