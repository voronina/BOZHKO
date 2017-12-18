#include <limits.h>

class DIJKSTRA {
private:

	vector<VERTEX> LIST;
	int V;
	double* distance;
	int* parents;

	double MAX_WEI;
	int TERM;

	vector<POINT> PATH;
	
public:
	DIJKSTRA(vector<VERTEX> new_LIST, double new_MAX_WEI) : LIST(new_LIST), MAX_WEI(new_MAX_WEI)//, TERM(new_TERM)
	{
		TERM = LIST.size();
		for (int i = 0; i < LIST.size(); i++) if (LIST[i].g_O_NUM() == -2) TERM = i;

		V = new_LIST.size();
		distance = (double*)malloc(V * sizeof(double));
		parents = (int*)malloc(V * sizeof(int));
	};

	vector<POINT> algo();

	double is_neight(int u, int i);

	vector<POINT> get_path();
	void print_path();

};