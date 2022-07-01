#include "types.h"
#include "stat.h"
#include "user.h"

int main() {
      changePolicy(0);
      int children = 0;
    for (int i = 0; i <10 ; i++) {
        int pid = fork();
        if ( pid == 0) {
            for (int i = 0; i < 10; i++) {
                printf(1, "/%d/ : /%d/\n", getpid(), i);
            }
            sleep(300);
            exit();
        }
        else children= children +1;
    }

    int sumTurnaround = 0;
    int sumWaiting = 0;
    int sumBurst = 0;
    
    

    for (int i = 0; i <10 ; i++) {
        int pid = wait();
        int waitingTime = getProcStatus(4, pid);
        int sleeping = getProcStatus(5, pid);
        int cpuBurst = getProcStatus(3, pid);
        int turnAround = waitingTime + sleeping+cpuBurst;
        sumTurnaround += turnAround;
        sumWaiting += waitingTime;
        sumBurst += cpuBurst;
        printf(1, "pid: %d, ", getpid());
        printf(1, "creation time = %d, ", getProcStatus(1, pid));
        printf(1, "turnaround time = %d, ", turnAround);
        printf(1, "waiting time = %d, ", waitingTime);
        printf(1, "sleeping time = %d, ", sleeping);
        printf(1, "cpu burst = %d, ", cpuBurst);
        printf(1,"\n");


    }
   
    double avgTurnaround = (double) sumTurnaround / 10;
    double avgWaiting = (double) sumWaiting / 10;
    double avgCBT = (double) sumBurst / 10;
    printf(1, "\naverage turnaround time: %lf\n",avgTurnaround);
    printf(1, "average waiting time: %lf\n",avgWaiting);
    printf(1, "average cpu burst time: %lf\n",avgCBT);
    printf(1,"Number of children: %d\n",children);
    exit();
}