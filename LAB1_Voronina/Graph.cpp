#include "Header.h"


// Создание графа
void GRAPH_CREATOR::graph_creator(int P_AMO)
{
	print_open_close();

	int CUR_NUM = OPEN[0];
	int CURR_O_NUM;
	POINT CUR_P = LIST[CUR_NUM].POINT_GR;

	for (int i = 0; i < P_AMO - 1; i++)
	{
		CUR_NUM = OPEN[0];   
		CUR_P = LIST[CUR_NUM].POINT_GR;
		CURR_O_NUM = LIST[CUR_NUM].O_NUM;

		for (int j = 0; j < O.size(); j++)
		{
			if (j != CURR_O_NUM)  curr_line_vec = create_lines(j, CUR_NUM, CUR_P);
		}

		curr_line_vec = create_line_to_term(CUR_P, CUR_NUM, TERM);

		if (curr_line_vec.begin() != curr_line_vec.end()) new_lines.insert(new_lines.end(), curr_line_vec.begin(), curr_line_vec.end());

		curr_line_vec.clear();

		CLOSE.push_back(OPEN[0]);
		OPEN.erase(OPEN.begin());

		print_open_close();
	}

	for (int i = 0; i < LIST.size(); i++)
	{
		LIST[i].print_vertex();
	}
}









// Проведение новой линии
vector<LINE> GRAPH_CREATOR::create_lines(int j, int CUR_NUM, POINT P)
{
	POINT* P_curr = O[j].g_P();
	for (int i = 0; i < O[j].g_N(); i++)
	{
		LINE curr_line = curr_line.create_line(P, P_curr[i]);
		if (check_new_line(curr_line))
		{
			curr_line_vec.push_back(curr_line);
			create_new_bound(P, P_curr[i], j, CUR_NUM);
		}
	}
	return curr_line_vec;
}

// Соединение с терминальной вершиной
vector<LINE> GRAPH_CREATOR::create_line_to_term(POINT CUR_P, int CUR_NUM, POINT TERM)
{
	// Проверка для терминальной вершины
	LINE curr_line = curr_line.create_line(CUR_P, TERM);
	if (check_new_line(curr_line) && !already_exist(TERM))
	{ 
		curr_line_vec.push_back(curr_line);
		create_new_bound(CUR_P, TERM, -2, CUR_NUM);
	}
	return curr_line_vec;
}






// Создание новой связи
void GRAPH_CREATOR::create_new_bound(POINT P1, POINT P2, int j, int CUR_NUM)
{
	int num = already_exist(P2);
	if ( num == -1 )
	{
		VERTEX NEW_V(NUM_VER, j, P2);
		NEW_V.add_neigh(CUR_NUM);
		LIST[CUR_NUM].add_neigh(NUM_VER);
		LIST.push_back(NEW_V);
		OPEN.push_back(NUM_VER);
		NUM_VER++;
	}
	else
	{
		LIST[num].add_neigh(CUR_NUM);
		LIST[CUR_NUM].add_neigh(NUM_VER);
	}
}

// Проверка на существование вершины
int GRAPH_CREATOR::already_exist(POINT P)
{
	for (int i = 0; i < LIST.size(); i++) if ((LIST[i].POINT_GR).equivalent(P)) return LIST[i].NUM;
	return -1;
}






// Проверка на пересечение с существующими линиями
bool GRAPH_CREATOR::check_new_line(LINE L_curr)
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


// Печать данных о вершине
void VERTEX::print_vertex()
{
	cout << endl << " NUM = " << NUM << " O_NUM = " << O_NUM << endl;
	POINT_GR.print_point();
	cout << " NEI = ";
	for (int i = 0; i < neigh.size(); i++) cout << neigh[i] << "; ";
	cout << endl << endl;
}
