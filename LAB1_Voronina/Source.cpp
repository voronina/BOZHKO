#include "Header.h"

int main()
{
	SourceData data = json_reader();

	// Стартовая и конечная точки
	POINT ST = data.startPoint;
	POINT TERM = data.endPoint;
	cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
	cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

	// Инициализация границ и препятствий
	OBS B = border_create(ST, TERM);
	B.obs_print(-1);
	vector<OBS> O = data.polygons;
	for (int i = 0; i < O.size(); i++) O[i].obs_print(i+1);

	O.push_back(B);

	int P_AMO = 2;
	for (int i = 0; i < O.size(); i++) P_AMO += O[i].g_N();

	GRAPH_CREATOR GR_CREATOR(ST, TERM, O);
	GR_CREATOR.graph_creator(P_AMO);
	vector<VERTEX> LIST = GR_CREATOR.g_LIST();

	int TERM_NUM = LIST.size();
	for (int i = 0; i < LIST.size(); i++) if (LIST[i].g_O_NUM() == -2) TERM_NUM = i;

	double MAX_WEI = GR_CREATOR.find_weight(B.g_P()[0], B.g_P()[2]) + 1000;
	DIJKSTRA DIJ(LIST, MAX_WEI, TERM_NUM);

	vector<int> PATH = DIJ.algo();

	cout << endl << "PATH = " << endl;
	for (int i = PATH.size() - 1; i >= 0; i--) cout << PATH[i] << " ";
	cout << endl;

	system("pause");
	return 0; 
}

