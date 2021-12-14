#include<bits/stdc++.h>
using namespace std;
int main(){

    int requests[] = {82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int distance =0;
    for(int i=0;i<7;i++){
        int sd = abs(head-requests[i]);
        distance+=sd;
        head=requests[i];
    }

    cout<<distance;
}
    