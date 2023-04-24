 
#include <stdio.h>
int main()
{
    int pid[15];
    int bt[15];
    int n;
    printf("Enter number of process:\n");
    scanf("%d",&n);
    
    printf("Enter process id of all the processes:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&pid[i]);
    }
    
    printf("Enter burst time of all the processes:\n");
    for(int i=0;i<n;i++){
        scanf("%d",&bt[i]);
    }
    
    int wt[n];
    wt[0] = 0;
    
    for(int i=1; i<=n;i++){
        wt[i] = wt[i-1] + bt[i-1];
    }
    int tat[n];
    for(int i=0;i<n;i++){
        tat[i] = wt[i] + bt[i];
    }
    
    float twt=0.0;
    float ttat=0.0;
    printf("Process ID      burst Time      Waiting Time    Turn-around timt\n");
    for(int i=0 ; i<n; i++){
        printf("%d\t\t",pid[i]);
         printf("%d\t\t",bt[i]);
          printf("%d\t\t",wt[i]);
           printf("%d\t\t",tat[i]);
           printf("\n");
           twt = twt + wt[i];
           ttat = ttat + tat[i];
    }
    
    float avg_wt;
    float avg_tat;
    avg_wt = twt / n;
    avg_tat = ttat / n;
    printf("Avg. waiting time = %f\n",avg_wt);
    printf("Avg. turnaround time = %f",avg_tat);
    
    
    
}
