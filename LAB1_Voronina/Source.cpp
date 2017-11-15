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

	POINT CUR_P = ST;
	vector<LINE> NEW_L;
	vector<LINE> CUR_L;
	
	int O_NUM = -1;

	for (int j = 0; j < O.size(); j++) 
	{ 
		if (j != O_NUM) 
		{
			CUR_L = new_lines(CUR_L, NEW_L, O, j, CUR_P);
		}
	}
	// Проверка для терминальной вершины
	LINE curr_line = curr_line.create_line(CUR_P, TERM);
	if (check_new_line(NEW_L, O, curr_line)) {	CUR_L.push_back(curr_line); }

	NEW_L.insert(NEW_L.end(), CUR_L.begin(), CUR_L.end());
	CUR_L.clear();


	cout << endl << "NEW_L.size() = " << NEW_L.size() << endl;



	POINT TEST(3.5, 6);

	O_NUM = 0;
	CUR_P = TEST;

	for (int j = 0; j < O.size(); j++)
	{
		if (j != O_NUM)
		{
			CUR_L = new_lines(CUR_L, NEW_L, O, j, CUR_P);
		}
	}
	// Проверка для терминальной вершины
	curr_line = curr_line.create_line(CUR_P, TERM);
	if (check_new_line(NEW_L, O, curr_line)) {	CUR_L.push_back(curr_line); }

	NEW_L.insert(NEW_L.end(), CUR_L.begin(), CUR_L.end());
	CUR_L.clear();
	
	cout << endl << "NEW_L.size() = " << NEW_L.size() << endl;

	system("pause");
	return 0; 
}

// Проведение новой линии
vector<LINE> new_lines(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, int j, POINT P)
{
	POINT* P_curr = O[j].g_P();

	for(int i = 0; i < O[j].g_N(); i++ )
	{
		LINE curr_line = curr_line.create_line(P, P_curr[i]);
		if ( check_new_line(new_lines, O, curr_line))
		{
			curr_line_vec.push_back(curr_line);
		}
	}
	return curr_line_vec;
}

// Проверка на пересечение с существующими линиями
bool check_new_line(vector<LINE> new_lines, vector<OBS> O, LINE L_curr)
{
	POINT inter(0, 0);

	int ans1 = 0;
	for (int i = 0; i < O.size(); i++)
	{
		ans1 = 0;
		for (int j = 0; j < O[i].g_N(); j++)
		{
			inter.zero_point();
			if (L_curr.intersect(L_curr, (O[i].g_L())[j], inter)) ans1++;
			if (inter.equivalent(L_curr.g_P1())) ans1--;
			if( inter.equivalent(L_curr.g_P2()) )  ans1--;
			if (L_curr.equivalent(L_curr, (O[i].g_L())[j])) ans1++;
			if (ans1 > 0)	{ return false; }
		}
	}

	int ans2 = 0;
	for (int i = 0; i < new_lines.size(); i++)
	{
		ans2 = 0;
		inter.zero_point();
		if (L_curr.intersect(L_curr, new_lines[i], inter)) ans2++;
		if (inter.equivalent(L_curr.g_P1())) ans2--;
		if (inter.equivalent(L_curr.g_P2()))  ans2--;
		if (L_curr.equivalent(L_curr, new_lines[i])) ans2 ++;
		if (ans2 > 0) {	return false; }
	}

	return true;
}