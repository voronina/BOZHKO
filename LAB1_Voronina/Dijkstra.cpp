#include "Header.h"


vector<POINT> DIJKSTRA::algo()
{
	int st = 0;
	int count, index, i, u, m = st + 1;
	double curr_wei = -1;

	int * visited = (int*)malloc(V * sizeof(int));

	for (i = 0; i < V; i++)
	{
		distance[i] = MAX_WEI;
		visited[i] = false;
		parents[i] = -1;
	}
	distance[st] = 0;
	parents[st] = -1;

	for (count = 0; count < V - 1; count++)
	{
		double min = MAX_WEI;
		for (i = 0; i < V; i++)
		{
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i];
				index = i;
			}
		}
		u = index;
		visited[u] = true;
		for (i = 0; i < V; i++)
		{
			curr_wei = is_neight(u, i);

			if (!visited[i] && curr_wei > 0 && distance[u] != MAX_WEI && distance[u] + curr_wei < distance[i])
			{
				distance[i] = distance[u] + curr_wei;
				parents[i] = u;
			}
		}
	}

	return get_path();
}


// Проверка на соседство
double DIJKSTRA::is_neight(int u, int i)
{
	double res = -1.0;
	vector<int> NEI = LIST[u].g_nei();
	vector<double> WEI = LIST[u].g_wei();

	if (u == i) return res;

	for (int j = 0; j < NEI.size(); j++)
	{
		if (NEI[j] == i) res = WEI[j];
	}

	return res;
}

// Получение пути
vector<POINT> DIJKSTRA::get_path()
{
	int curr_V = TERM;

	while (curr_V >= 0)
	{
		PATH.push_back(LIST[curr_V].g_P());
		curr_V = parents[curr_V];
	}

	return PATH;
}

void DIJKSTRA::print_path()
{
	cout << endl << endl << endl << "PATH: " << endl << endl;

	int k = 1;
	for (int i = PATH.size() - 1; i >= 0; i--)
	{
		cout << "POINT # " << k << ": ";
		PATH[i].print_point();
		k++;
	}
	cout << endl;
}