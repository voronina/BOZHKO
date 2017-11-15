#include "Header.h"


int main()
{
	// Инициализация границ и препятствий
	OBS B = border_read();
	OBS* O = OBS_read();

	// Стартовая и конечная точки
	POINT ST(1,1);
	POINT TERM(9,9);
	cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
	cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

	vector<LINE> NEW_L = new_lines(NEW_L,B,ST);

	cout << NEW_L.size() << endl;
	

	// Попытка соединения с вершинами поля
	for (int i = 0; i < NEW_L.size(); i++) { cout << NEW_L[i].g_A() << " " << NEW_L[i].g_B() << " " << NEW_L[i].g_C() << endl; }
	cout << endl;



	//POINT test_point(2, 0.5);
	//cout << O[0].inside_border(test_point) << endl;

	system("pause");
	return 0; 
}


vector<LINE> new_lines(vector<LINE> new_lines, OBS O, POINT P)
{
	POINT* P_curr = O.g_P();

	for(int i = 0; i < O.g_N(); i++ )
	{
		LINE curr_line = curr_line.create_line(P, P_curr[i]);
		new_lines.push_back(curr_line);
	}
	return new_lines;
}





 
