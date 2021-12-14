#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<int> requests{82, 170, 43, 140, 24, 16, 190};
    int head = 50;
    int distance = 0;
    int max_left_index, min_right_index = -1;
    string direction = "right";
    sort(requests.begin(), requests.end());
    for (int i = 0; i < requests.size(); i++)
    {
        if (requests[i] > head)
        {
            max_left_index = i - 1;
            min_right_index = i;
            break;
        }
    }
    if (direction == "left")
    {
        if (max_left_index == -1)
        {
            distance = requests[6] - head;
        }
        else
        {

            distance = head + 199 + (199-requests[min_right_index]);
        }
    }
    else
    {
        if (min_right_index == -1)
        {
            distance = head - requests[0];
        }
        else
        {
            distance = (199 - head) + (199 + requests[max_left_index]);
        }
    }
    cout << "Distance is " << distance;
}