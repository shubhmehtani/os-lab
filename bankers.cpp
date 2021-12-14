#include <iostream>

using namespace std;

int main()
{
    int a = 10, b = 5, c = 7;
    int suma = 0, sumb = 0, sumc = 0;
    int allocation[5][3], maxneed[5][3], available[3], remaining[5][3];
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter the allocation for process " << i << endl;
        cin >> allocation[i][0] >> allocation[i][1] >> allocation[i][2];
        suma += allocation[i][0];
        sumb += allocation[i][1];
        sumc += allocation[i][2];
    }
    for (int i = 0; i < 5; i++)
    {
        cout << "Enter the allocation for max " << i << endl;
        cin >> maxneed[i][0] >> maxneed[i][1] >> maxneed[i][2];
    }
    for (int i = 0; i < 5; i++)
    {
        remaining[i][0] = maxneed[i][0] - allocation[i][0];
        remaining[i][1] = maxneed[i][1] - allocation[i][1];
        remaining[i][2] = maxneed[i][2] - allocation[i][2];
    }
    available[0] = a - suma;
    available[1] = b - sumb;
    available[2] = c - sumc;

    int counter = 0;
    while (1)
    {
        if (available[0] == a && available[1] == b && available[2] == c)
        {
            break;
        }
        if (counter == 5)
        {
            cout << "Deadlock\n";
            break;
        }
        for (int i = 0; i < 5; i++)
        {
            if (available[0] >= remaining[i][0] && available[1] >= remaining[i][1] && available[2] >= remaining[i][2])
            {
                remaining[i][0] = INT_MAX;
                remaining[i][1] = INT_MAX;
                remaining[i][2] = INT_MAX;
                cout << "Process " << i << " ";
                available[0] += allocation[i][0];
                available[1] += allocation[i][1];
                available[2] += allocation[i][2];
            }
            else
            {
                counter++;
            }
        }
    }
}