#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> requests{82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int distance = 0;
    int i = 0;
    while (i < 7)
    {
        int min = abs(head - requests[0]);
        int sd;
        int min_index = 0;
        for (int j = 1; j < requests.size(); j++)
        {
            sd = abs(head - requests[j]);
            if (sd < min)
            {
                min = sd;
                min_index = j;
            }
        }
        cout << min << endl;
        distance += min;
        head = requests[min_index];
        requests.erase(requests.begin() + min_index);
        i++;
    }
    cout << "The distance is " << distance;
}