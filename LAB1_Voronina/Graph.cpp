#include "Header.h"

// Создание графа
void GRAPH_CREATOR::graph_creator()
{
	bool ans = false;
	int CUR_NUM = 0;

	//print_open_close();

	//while (ans == false && OPEN.size() > 0)
	int k = 0;
	while(k<4)
	{
		k++;

		if (OPEN.size() == 0) break;

		while (!on_free_space(LIST[OPEN[0]].g_P()) && OPEN.size() > 1)
		{
			CLOSE.push_back(OPEN[0]);
			OPEN.erase(OPEN.begin());
		}
		
		CUR_NUM = OPEN[0];

		ans = all_new_lines(CUR_NUM);

		CLOSE.push_back(OPEN[0]);
		OPEN.erase(OPEN.begin());

		//print_open_close();
	}

	for (int i = 0; i < LIST.size(); i++)
	{
		LIST[i].print_vertex();
	}

}









/****************************************************************************************************************/
// Проведение всех возможных линий из текущей точки
bool GRAPH_CREATOR::all_new_lines(int CUR_NUM)
{
	bool ans = false;

	int CURR_O_NUM = LIST[CUR_NUM].O_NUM;
	POINT CUR_P = LIST[CUR_NUM].POINT_GR;

	//cout << "CUR_P = ";
	//CUR_P.print_point();

	for (int j = 0; j < O.size(); j++)
	{
		if (j != CURR_O_NUM)  curr_line_vec = create_lines(j, CUR_NUM, CUR_P);
		//else  curr_line_vec = create_into_obs(j, CUR_NUM, CUR_P);
	}

	//int prev_size = curr_line_vec.size();

	//curr_line_vec = create_line_to_term(CUR_P, CUR_NUM, TERM);

	//if (curr_line_vec.size() - prev_size > 0) ans = true;

	if (curr_line_vec.begin() != curr_line_vec.end()) new_lines.insert(new_lines.end(), curr_line_vec.begin(), curr_line_vec.end());

	curr_line_vec.clear();

	return ans;
}

// Проведение новой линии
vector<LINE> GRAPH_CREATOR::create_lines(int j, int CUR_NUM, POINT P)
{
	vector<POINT> P_curr = O[j].g_P();
	for (int i = 0; i < P_curr.size(); i++)
	{
		if (!on_free_space(P_curr[i])) { continue; }

		LINE curr_line(P, P_curr[i]);

		// ПРОВЕРА 0-3 0-61
		if (check_O(curr_line) && check_new_lines(curr_line))
		{
			curr_line_vec.push_back(curr_line);
			create_new_bound(P, P_curr[i], j, CUR_NUM);
		}
	}
	return curr_line_vec;
}

/****************************************************************************************************************/
// Проверка на принадледность свободной области
bool GRAPH_CREATOR::on_free_space(POINT P_check)
{
	// Проверка на принадлежность полю
	if (!B.inside_border(P_check)) return false;

	// Проверка на попадание в одно из препятствий 
	for (int i = 0; i < O.size(); i++) if (O[i].inside_border(P_check))  return false; 

	return true;
}


bool GRAPH_CREATOR::check_O(LINE L_curr)
{
	for (int i = 0; i < O.size(); i++)
	{
		for (int j = 0; j < O[i].g_L().size(); j++)
		{
			LINE ob = O[i].g_L()[j];
			if (L_curr.intersect_segm_without_P(ob)) 	return false; 
		}
	}
	return true;
}

bool GRAPH_CREATOR::check_new_lines(LINE L_curr)
{
	for (int i = 0; i < new_lines.size(); i++)
	{
		LINE ob = new_lines[i];
		if (L_curr.intersect_segm_without_P(ob)) 	return false;
	}
	return true;
}














/*
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
		if (check_new_line(L1, 1))//  && on_free_space(L1.g_P1()) && on_free_space(L1.g_P2())
		{
			curr_line_vec.push_back(L1);
			POINT P2_1 = (P.equivalent(L1.g_P1())) ? (L1.g_P2()) : L1.g_P1();
			create_new_bound(P, P2_1, j, CUR_NUM);
		}

		LINE L2 = (O[j].g_L())[numb2];
		if (check_new_line(L2, 1)) //(&& on_free_space(L2.g_P1()) && on_free_space(L2.g_P2())
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
}*/







/****************************************************************************************************************/
// Создание новой связи
void GRAPH_CREATOR::create_new_bound(POINT P1, POINT P2, int j, int CUR_NUM)
{
	int num = already_exist(P2);
	double w = find_weight(P1, P2);

	if (num == -1)
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


/****************************************************************************************************************/
// Печать данных о вершине
void VERTEX::print_vertex()
{
	cout << endl << "VER = " << NUM << endl;
	POINT_GR.print_point();
	cout << "NEI = ";
	for (int i = 0; i < neigh.size(); i++) cout << neigh[i] << "; ";
	cout << endl;
	//cout << "WEI = ";
	//for (int i = 0; i < weight.size(); i++) cout << weight[i] << "; ";
	//cout << endl << endl;
}
















/*
void GRAPH_CREATOR::new_L(int CUR_NUM)
{
POINT curr_P = LIST[CUR_NUM].g_P();

for (int i = 0; i < O.size(); i++)
{
if (i != LIST[CUR_NUM].g_O_NUM)
{
for (int j = 0; j < O[i].g_P().size(); j++)
{
LINE new_L = new_L.create_line(curr_P, O[i].g_P()[j]);

}
}
}
}

bool GRAPH_CREATOR::check_L(LINE curr_L)
{
for (int i = 0; i < O.size(); i++)
{
for (int j = 0; j < O[i].g_L().size(); j++)
{
if(curr_L.L_curr.intersect(L_curr, (O[i].g_L())[j], inter))
}
}
}*/
