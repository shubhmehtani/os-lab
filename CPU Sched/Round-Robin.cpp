#include <iostream>
using namespace std;

void updateQueue(int queue[], int timer, int arrival[], int n, int maxProcessInd){
    int zeroInd;
    for(int i=0; i<n; i++){
        if(queue[i]==0){
            zeroInd=i;
            break;
        }
    }
    queue[zeroInd] = maxProcessInd + 1;
}

void maintainQueue(int queue[], int n){
    for(int i=0; (i<n-1)&&(queue[i+1]!=0); i++){
        int temp=queue[i];
        queue[i]=queue[i+1];
        queue[i+1]=temp;
    }
}

void checkNewArr(int timer, int arrival[], int n, int maxProcessInd, int queue[]){
    if(timer <= arrival[n-1]){
        bool newArr = false;
        for(int j=(maxProcessInd+1); j<n; j++){
            if(arrival[j]<=timer){
                if(maxProcessInd<j){
                    maxProcessInd=j;
                    newArr=true;
                }
            }
        }
        if(newArr){
            updateQueue(queue, timer, arrival, n, maxProcessInd);
        }
    }
}

int main(){
    int n, timeQuanta;
    int timer=0, maxProcessInd=0;
    float avgWait=0, avgTurnAroundTime=0;
    cout << "Num of processes" << endl;
    cin >> n;
    cout << "Time Quanta" << endl;
    cin >> timeQuanta;

    int arrTime[n], burstTime[n], waitTime[n], turnAroundTime[n], queue[n], tempBurst[n];
    bool complete[n];

    cout << "Arrival time of the processes" << endl;
    for(int i=0; i<n; i++){
        cin >> arrTime[i];
    }

    cout << "Burst time of the processes" << endl;
    for(int i=0; i<n; i++){
        cin >> burstTime[i];
        tempBurst[i]=burstTime[i];
    }

    for(int i=0; i<n; i++){
        complete[i] = false;
        queue[i] = 0;
    }

    while(timer<arrTime[0]){
        timer++;
    }
    queue[0] = 1;

    while(true){
        bool flag=true;
        for(int i=0; i<n; i++){
            if(tempBurst[i]!=0){
                flag=false;
                break;
            }
        }
        if(flag){
            break;
        }
        for(int i=0; (i<n)&&(queue[i]!=0); i++){
            int ctr=0; 
            while((ctr<timeQuanta)&&(tempBurst[queue[0]-1]>0)){
                tempBurst[queue[0]-1] -=1;
                timer+=1;
                ctr++;
                checkNewArr(timer, arrTime, n, maxProcessInd, queue);
            }
            if((tempBurst[queue[0]-1]==0)&&(complete[queue[0]-1]==false)){
                turnAroundTime[queue[0]-1] = timer;
                complete[queue[0]-1]=true;
            }
            bool idle=true;
            if(queue[n-1]==0){
                for(int i=0; i<n && queue[i]!=0; i++){
                    if(complete[queue[i]-1]==false){
                        idle=false;
                    }
                }
            }
            else{
                idle=false;
            }
            if(idle){
                timer++;
                checkNewArr(timer, arrTime, n, maxProcessInd, queue);
            }
            maintainQueue(queue, n);
        }
    }
    for(int i=0; i<n; i++){
        turnAroundTime[i] = turnAroundTime[i]-arrTime[i];
        waitTime[i] = turnAroundTime[i] - burstTime[i];
    }

    cout << "\nProgram No.\tArrival Time\tBurst Time\tWait Time\tTurnAround Time"<< endl;
    for(int i=0; i<n; i++){
        cout <<i+1<<"\t\t"<<arrTime[i] <<"\t\t"<<burstTime[i]<<"\t\t"<<waitTime[i]<<"\t\t"<<turnAroundTime[i]<<endl; 
    }
    for(int i=0; i<n; i++){
        avgWait+=waitTime[i];
        avgTurnAroundTime+=turnAroundTime[i];
    }
    cout << "Average wait time " << float(avgWait/n) << endl;
    cout << "Average turn around time " << float(avgTurnAroundTime/n);


}