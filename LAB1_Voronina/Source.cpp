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

	//int counter = 0;
	//for (int i = 0; i < O.size(); i++)
		
	//vector<VERTEX> OPEN;

	GRAPH GR(ST, TERM);

	GR.graph_creator(O);

	system("pause");
	return 0; 
}

