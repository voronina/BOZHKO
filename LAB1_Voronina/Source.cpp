#include "Header.h"


int main()
{
	// Инициализация границ и препятствий
	OBS B = border_read();
	vector<OBS> O = OBS_read();

	// Стартовая и конечная точки
	POINT ST(1,1);
	POINT TERM(9,9);
	cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
	cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

	O.push_back(B);

	int P_AMO = 2;
	for (int i = 0; i < O.size(); i++) P_AMO += O[i].g_N();

	cout << " A = " << P_AMO << endl;

	//int counter = 0;
	//for (int i = 0; i < O.size(); i++)
		
	//vector<VERTEX> OPEN;

	GRAPH_CREATOR GR_CREATOR(ST, TERM, O);

	GR_CREATOR.graph_creator(P_AMO);

	system("pause");
	return 0; 
}

