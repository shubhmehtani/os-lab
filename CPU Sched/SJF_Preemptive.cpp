#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
using namespace std;

class Process
{
public:
	string a;
	int a1;
	int a2;
};
void waitingTime(Process p[], int n, int wait[])
{
	int rt[n];
	for (int i = 0; i < n; i++){
		rt[i] = p[i].a2;
	}

	int comp = 0, t = 0, minm = INT_MAX, shortest = 0, finish_time;
	bool check = false;
	while (comp != n)
	{
		for (int j = 0; j < n; j++)
		{
			if ((p[j].a1 <= t) &&
				(rt[j] < minm) && rt[j] > 0)
			{
				minm = rt[j];
				shortest = j;
				check = true;
			}
		}

		if (check == false)
		{
			t++;
			continue;
		}
		rt[shortest]--;
		minm = rt[shortest];
		if (minm == 0)
			minm = INT_MAX;
		if (rt[shortest] == 0)
		{
			comp++;
			check = false;
			finish_time = t + 1;
			wait[shortest] = finish_time - p[shortest].a2 - p[shortest].a1;

			if (wait[shortest] < 0)
				wait[shortest] = 0;
		}
		t++;
	}
}
void turnAroundTime(Process p[], int n, int wait[], int turn_around[])
{
	for (int i = 0; i < n; i++)
		turn_around[i] = p[i].a2 + wait[i];
}

void avgTime(Process p[], int n)
{
	int wait[n], turn_around[n], total_wt = 0, total_turn_around = 0;
	waitingTime(proc, n, wt);
	turnAroundTime(proc, n, wt, turn_around);
	int s = 0;
	cout << "Turn Around Time :" << endl;
	for (int i = 0; i < n; i++)
	{
		int d = turn_around[i];
		s = s + d;
		cout << p[i].a << "  : " << d << endl;
	}
	cout << "" << endl;
	cout << "Average turn around time = " << (float)s / n << endl;
	cout << "" << endl;
	cout << "" << endl;
	cout << "Waiting Time :" << endl;
	s = 0;
	for (int i = 0; i < n; i++)
	{
		int d = wait[i];
		s = s + d;
		cout << p[i].a << "  : " << d << endl;
	}
	cout << "" << endl;
	cout << "Average waiting time = " << (float)s / n << endl;
}
int main()
{
	int process;
	cin >> process;
	Process p[n];
	for (int i = 0; i < process; i++)
	{
		cout << "Process " << i + 1 << endl;
		cout << "Enter Process Id: ";
		cin >> p[i].a;
		cout << "Enter Arrival Time: ";
		cin >> p[i].a1;
		cout << "Enter Burst Time: ";
		cin >> p[i].a2;
	}
	int n1 = sizeof(proc) / sizeof(p[0]);
	cout << "" << endl;
	avgTime(proc, n1);
	return 0;
}
