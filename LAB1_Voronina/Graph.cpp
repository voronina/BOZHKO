#include "Header.h"

// Проведение новой линии
vector<LINE> GRAPH::create_lines(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, int j, POINT P)
{
	POINT* P_curr = O[j].g_P();
	for (int i = 0; i < O[j].g_N(); i++)
	{
		LINE curr_line = curr_line.create_line(P, P_curr[i]);
		if (check_new_line(new_lines, O, curr_line))
		{
			curr_line_vec.push_back(curr_line);
			VERTEX NEW_V(NUM_VER, j, P_curr[i]);
			OPEN.push_back(NEW_V);
			LIST.push_back(NEW_V);
			NUM_VER++;
		}
	}
	return curr_line_vec;
}

// Соединение с терминальной вершиной
vector<LINE> GRAPH::create_line_to_term(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, POINT CUR_P, POINT TERM)
{
	// Проверка для терминальной вершины
	LINE curr_line = curr_line.create_line(CUR_P, TERM);
	if (check_new_line(new_lines, O, curr_line))
	{ 
		curr_line_vec.push_back(curr_line);
		VERTEX NEW_V(NUM_VER, -2, TERM);
		OPEN.push_back(NEW_V);
		LIST.push_back(NEW_V);
		NUM_VER++;
	}

	return curr_line_vec;
}

// Проверка на пересечение с существующими линиями
bool GRAPH::check_new_line(vector<LINE> new_lines, vector<OBS> O, LINE L_curr)
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
			if (inter.equivalent(L_curr.g_P2()))  ans1--;
			if (L_curr.equivalent(L_curr, (O[i].g_L())[j])) ans1++;
			if (ans1 > 0) { return false; }
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
		if (L_curr.equivalent(L_curr, new_lines[i])) ans2++;
		if (ans2 > 0) { return false; }
	}

	return true;
}

// Создание графа
void GRAPH::graph_creator(vector<OBS> O)
{
	POINT CUR_P = CLOSE[0].POINT_GR;
	vector<LINE> CUR_L, NEW_L;

	int NUM_VER = 1;
	for (int i = 0; i < 2; i++)
	{
		CUR_P = CLOSE[0].POINT_GR;
		if (i == 1)
		{
			POINT TEST(3.5, 6);
			CUR_P = TEST;
		}

		int O_NUM = -1;
		for (int j = 0; j < O.size(); j++)
		{
			if (j != O_NUM)  CUR_L = create_lines(CUR_L, NEW_L, O, j, CUR_P);
		}

		CUR_L = create_line_to_term(CUR_L, NEW_L, O, CUR_P, TERM);

		if (CUR_L.begin() != CUR_L.end()) NEW_L.insert(NEW_L.end(), CUR_L.begin(), CUR_L.end());

		CUR_L.clear();
		cout << endl << "NEW_L.size() = " << NEW_L.size() << endl;
	}

	/*for (int i = 0; i < OPEN.size(); i++)
	{
	cout << " i = " << i << endl;
	OPEN[i].POINT_GR.print_point();
	}*/
}