#include "Header.h"

// Создание графа
void GRAPH_CREATOR::graph_creator(int P_AMO)
{
	print_open_close();

	LIST[OPEN[0]].g_P().print_point();

	//cout << on_free_space(LIST[OPEN[0]].g_P()) << endl;

	while (!on_free_space(LIST[OPEN[0]].g_P()) && OPEN.size() > 1)
	{
		CLOSE.push_back(OPEN[0]);
		OPEN.erase(OPEN.begin());
	}
	
	int CUR_NUM = OPEN[0];

	all_new_lines(CUR_NUM);

	CLOSE.push_back(OPEN[0]);
	OPEN.erase(OPEN.begin());

	print_open_close();

	//if (OPEN.size() == 0)

	// int CUR_NUM_PREV = CUR_NUM;

	/*print_open_close();

	int CUR_NUM = OPEN[0];
	int CURR_O_NUM;
	int i = 0;

	//for (int i = 0; i < P_AMO - 1; i++)
	while (OPEN.size() > 0)
	{
		cout << i << endl;
		i++;

		CUR_NUM = OPEN[0];
		CURR_O_NUM = LIST[CUR_NUM].O_NUM;

		all_new_lines(CUR_NUM);

		CLOSE.push_back(OPEN[0]);
		OPEN.erase(OPEN.begin());

		print_open_close();
	}*/

	/*for (int i = 0; i < LIST.size(); i++)
	{
	LIST[i].print_vertex();
	}*/
}

// Проверка на принадледность свободной области
bool GRAPH_CREATOR::on_free_space(POINT P_check)
{
	// Проверка на принадлежность полю
	if (!B.inside_border(P_check)) return false;

	// Проверка на попадание в одно из препятствий 
	for (int i = 0; i < O.size(); i++) if (O[i].inside_border(P_check)) { cout << " i = " << i << endl; return false; }

	return true;
}




































// Создание графа
/*void GRAPH_CREATOR::graph_creator(int P_AMO)
{
	print_open_close();

	int CUR_NUM = OPEN[0];
	int CURR_O_NUM;
	int i = 0;

	//for (int i = 0; i < P_AMO - 1; i++)
	while(OPEN.size() > 0)
	{
		cout << i << endl;
		i++;

		CUR_NUM = OPEN[0];   
		CURR_O_NUM = LIST[CUR_NUM].O_NUM;

		all_new_lines(CUR_NUM);

		CLOSE.push_back(OPEN[0]);
		OPEN.erase(OPEN.begin());

		print_open_close();
	}

	for (int i = 0; i < LIST.size(); i++)
	{
		LIST[i].print_vertex();
	}
}*/



// Проведение всех возможных линий из текущей точки
void GRAPH_CREATOR::all_new_lines(int CUR_NUM)
{
	int CURR_O_NUM = LIST[CUR_NUM].O_NUM;
	POINT CUR_P = LIST[CUR_NUM].POINT_GR;

	for (int j = 0; j < O.size(); j++)
	{
		if (j != CURR_O_NUM)  curr_line_vec = create_lines(j, CUR_NUM, CUR_P);
		else /*if (CURR_O_NUM != (O.size() - 1))*/ curr_line_vec = create_into_obs(j, CUR_NUM, CUR_P);
	}

	curr_line_vec = create_line_to_term(CUR_P, CUR_NUM, TERM);

	if (curr_line_vec.begin() != curr_line_vec.end()) new_lines.insert(new_lines.end(), curr_line_vec.begin(), curr_line_vec.end());

	curr_line_vec.clear();
}

// Проведение новой линии
vector<LINE> GRAPH_CREATOR::create_lines(int j, int CUR_NUM, POINT P)
{
	vector<POINT> P_curr = O[j].g_P();
	for (int i = 0; i < O[j].g_N(); i++)
	{
		LINE curr_line = curr_line.create_line(P, P_curr[i]);
		if (check_new_line(curr_line, 0))
		{
			curr_line_vec.push_back(curr_line);
			create_new_bound(P, P_curr[i], j, CUR_NUM);
		}
	}
	return curr_line_vec;
}

// Перенос связей из препятствий
vector<LINE> GRAPH_CREATOR::create_into_obs(int j, int CUR_NUM, POINT P)
{
	vector<POINT> P_curr = O[j].g_P();
	int numb2 = -1;
	for (int i = 0; i < O[j].g_N(); i++) if (P.equivalent(P_curr[i])) numb2 = i;

	if (numb2 != -1)
	{
		int numb1 = ((numb2 - 1) > 0) ? (numb2 - 1) : (O[j].g_N() - 1);

		LINE L1 = (O[j].g_L())[numb1];
		if (check_new_line(L1, 1))
		{
			curr_line_vec.push_back(L1);
			POINT P2_1 = (P.equivalent(L1.g_P1())) ? (L1.g_P2()) : L1.g_P1();
			create_new_bound(P, P2_1, j, CUR_NUM);
		}

		LINE L2 = (O[j].g_L())[numb2];
		if (check_new_line(L2, 1))
		{
			curr_line_vec.push_back(L2);
			POINT P2_2 = (P.equivalent(L2.g_P1())) ? (L2.g_P2()) : L2.g_P1();
			create_new_bound(P, P2_2, j, CUR_NUM);
		}
	}

	return curr_line_vec;
}

// Соединение с терминальной вершиной
vector<LINE> GRAPH_CREATOR::create_line_to_term(POINT CUR_P, int CUR_NUM, POINT TERM)
{
	// Проверка для терминальной вершины
	LINE curr_line = curr_line.create_line(CUR_P, TERM);

	if (check_new_line(curr_line, 2))
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
	double w = find_weight(P1, P2);

	if ( num == -1 )
	{
		VERTEX NEW_V(NUM_VER, j, P2, CUR_NUM);

		NEW_V.add_neigh(CUR_NUM);
		NEW_V.add_weight(w);

		LIST[CUR_NUM].add_neigh(NUM_VER);
		LIST[CUR_NUM].add_weight(w);

		LIST.push_back(NEW_V);
		OPEN.push_back(NUM_VER);
		NUM_VER++;
	}
	else
	{
		LIST[num].add_neigh(CUR_NUM);
		LIST[num].add_weight(w);

		LIST[CUR_NUM].add_neigh(num);
		LIST[CUR_NUM].add_weight(w);
	}
}

// Проверка на существование вершины
int GRAPH_CREATOR::already_exist(POINT P)
{
	for (int i = 0; i < LIST.size(); i++) if ((LIST[i].POINT_GR).equivalent(P)) return LIST[i].NUM;
	return -1;
}

// Нахождение веса ребра
double GRAPH_CREATOR::find_weight(POINT P1, POINT P2)
{
	double XX = P2.g_X() - P1.g_X();
	double YY = P2.g_Y() - P1.g_Y();
	double res = sqrt(pow(XX, 2) + pow(YY, 2));
	return res;
}


// Проверка на пересечение с существующими линиями
bool GRAPH_CREATOR::check_new_line(LINE L_curr, int flag_obs)
{
	POINT inter(0, 0);

	int ans1 = 0;
	for (int i = 0; i < O.size(); i++)
	{
		for (int j = 0; j < O[i].g_N(); j++)
		{
			inter.zero_point();
			if (L_curr.intersect(L_curr, (O[i].g_L())[j], inter) && (!inter.equivalent(L_curr.g_P1()) && !inter.equivalent(L_curr.g_P2()))) { return false; }
			if (flag_obs < 1) { if (L_curr.equivalent(L_curr, (O[i].g_L())[j])) { return false; } }
		}
	}

	for (int i = 0; i < new_lines.size(); i++)
	{
		inter.zero_point();
		if (L_curr.intersect(L_curr, new_lines[i], inter) && (!inter.equivalent(L_curr.g_P1()) && !inter.equivalent(L_curr.g_P2()))) { return false; }
		if (flag_obs < 2) { if (L_curr.equivalent(L_curr, new_lines[i])) { return false; } }
	}

	return true;
}

// Печать данных о вершине
void VERTEX::print_vertex()
{
	cout << endl << "VER = " << NUM << /* " O_NUM = " << O_NUM <<  " PAR = " << PARENT <<*/ endl;
	POINT_GR.print_point();
	cout << "NEI = ";
	for (int i = 0; i < neigh.size(); i++) cout << neigh[i] << "; ";
	cout << endl;
	//cout << "WEI = ";
	//for (int i = 0; i < weight.size(); i++) cout << weight[i] << "; ";
	//cout << endl << endl;
}                        

