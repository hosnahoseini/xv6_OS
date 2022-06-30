#include "types.h"
#include "stat.h"
#include "user.h" 

int main(void)
{
    changePolicy(3);
    int i, p = 30;
    int pids[p];
    for(i=0;i<p;i++) {
        int pid = fork();
        int ticks = 6-(i/5);
        if(pid == 0) {
            changeTickets(getpid(), ticks * 10);
            for(int j=1;j<=250;j++)
                printf(1, "%d : %d\n", i, j);
            exit();
        } else {
            pids[i] = pid;
        }
    }
    
    for(i=0;i<p;i++)
        wait();

    int avg_tat = 0, avg_cbt = 0, avg_wt = 0;
    int class_tat = 0, class_cbt = 0, class_wt = 0;
    for(i=0;i<p;i++) {
        int pid = pids[i];
        int cbt = getProcStatus(3, pid);
        int tat = getProcStatus(2, pid) - getProcStatus(1, pid);
        int wt = getProcStatus(4, pid);
        printf(1, "Child %d, CPU Burst Time\t%d\n", pid, cbt);
        printf(1, "Child %d, Turn Around Time\t%d\n", pid, tat);
        printf(1, "Child %d, Waiting Time\t%d\n", pid, wt);
        printf(1, "\n");
        avg_tat += tat;
        avg_cbt += cbt;
        avg_wt += wt;
        class_tat += tat;
        class_cbt += cbt;
        class_wt += wt;
        if(i % 10 == 9) {
            class_tat /= 5.0f;
            class_cbt /= 5.0f;
            class_wt /= 5.0f;
            printf(1, "Average class %d,  CPU Burst Time\t%d\n", 6-i/5, class_cbt);
            printf(1, "Average class %d,  Turn Around Time\t%d\n", 6-i/5, class_tat);
            printf(1, "Average class %d,  Waiting Time\t%d\n", 6-i/5, class_wt);
            printf(1, "\n");

            class_tat = 0, class_cbt = 0, class_wt = 0;
        }
    }
    avg_tat /= (int)p;
    avg_cbt /= (int)p;
    avg_wt /= (int)p;

    printf(1, "Average CPU Burst Time\t%d\n", avg_cbt);
    printf(1, "Average Turn Around Time\t%d\n", avg_tat);
    printf(1, "Average Waiting Time\t%d\n", avg_wt);
    exit();
}
