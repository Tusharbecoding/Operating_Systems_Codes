//WAP to input three processes from user with arrival time and cpu time and find waiting time and show in form of a table
#include<iostream>
using namespace std;

int main()
{
    int n;
    cout<<"Enter the number of processes: ";
    cin>>n;
    int at[n],bt[n],wt[n],tat[n],ct[n];
    cout<<"Enter the arrival time and burst time of the processes: "<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"Process "<<i+1<<": ";
        cin>>at[i]>>bt[i];
    }
    wt[0]=0;
    for(int i=1;i<n;i++)
    {
        wt[i]=0;
        for(int j=0;j<i;j++)
        {
            wt[i]+=bt[j];
        }
        wt[i]-=at[i];
    }
    cout<<"Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"\t\t"<<at[i]<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<endl;
    }
    return 0;
}

