#include <limits.h>

class DIJKSTRA {
private:

	vector<VERTEX> LIST;
	int V;
	double* distance;
	int* parents;

	double MAX_WEI;
	int TERM;

	vector<int> PATH;
	
public:
	DIJKSTRA(vector<VERTEX> new_LIST, double new_MAX_WEI, int new_TERM) : LIST(new_LIST), MAX_WEI(new_MAX_WEI), TERM(new_TERM)
	{
		V = new_LIST.size();
		distance = (double*)malloc(V * sizeof(double));
		parents = (int*)malloc(V * sizeof(int));
	};

	vector<int> algo();

	double is_neight(int u, int i);

	vector<int> DIJKSTRA::get_path();

};