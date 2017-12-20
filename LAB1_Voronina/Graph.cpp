#include "Header.h"

// Создание графа
bool GRAPH_CREATOR::graph_creator()
{
	bool ans = false;
	int CUR_NUM = 0;

	//print_open_close();

	while (ans == false && OPEN.size() > 0)
	{
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

	return ans;
}

/****************************************************************************************************************/
// Проведение всех возможных линий из текущей точки
bool GRAPH_CREATOR::all_new_lines(int CUR_NUM)
{
	bool ans = false;

	int CURR_O_NUM = LIST[CUR_NUM].O_NUM;
	POINT CUR_P = LIST[CUR_NUM].POINT_GR;

	for (int j = 0; j < O.size(); j++)
	{
		if (j != CURR_O_NUM)  curr_line_vec = create_lines(j, CUR_NUM, CUR_P);
		else  curr_line_vec = create_into_obs(j, CUR_NUM, CUR_P);
	}

	ans = create_line_to_term(CUR_P, CUR_NUM);

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

		if (/*check_O(curr_line) && */check_new_lines(curr_line, new_lines) && check_new_lines(curr_line, curr_line_vec))
		{
			/*cout << endl << endl << "LINE TO " ;
			curr_line.g_P2().print_point();*/

			if (check_O(curr_line))
			{
				curr_line_vec.push_back(curr_line);
				create_new_bound(P, P_curr[i], j, CUR_NUM);
			}
		}
	}
	return curr_line_vec;
}

// Перенос связей из препятствий
vector<LINE> GRAPH_CREATOR::create_into_obs(int j, int CUR_NUM, POINT P)
{
	int n_in_O = -1;

	vector<POINT> P_vec = O[j].g_P();
	for (int i = 0; i < P_vec.size(); i++) if (P.equ(P_vec[i])) n_in_O = i;

	if (n_in_O != -1)
	{
		int n_nei = ((n_in_O - 1) > 0) ? (n_in_O - 1) : (O[j].g_N() - 1);

		LINE L1 = (O[j].g_L())[n_nei];
		L_inti_O(L1, j, CUR_NUM, P);

		LINE L2 = (O[j].g_L())[n_in_O];
		L_inti_O(L2, j, CUR_NUM, P);
	}

	return curr_line_vec;
}

// 
void GRAPH_CREATOR::L_inti_O(LINE L, int j, int CUR_NUM, POINT P)
{
	if (check_O(L) && check_new_lines(L, curr_line_vec) &&  on_free_space(L.g_P1()) && on_free_space(L.g_P2()) )
	{
		curr_line_vec.push_back(L);
		POINT P2 = (P.equ(L.g_P1())) ? (L.g_P2()) : L.g_P1();
		create_new_bound(P, P2, j, CUR_NUM);
	}
}

// Соединение с терминальной вершиной
bool GRAPH_CREATOR::create_line_to_term(POINT CUR_P, int CUR_NUM)
{
	// Проверка для терминальной вершины
	LINE curr_line(CUR_P, TERM);

	if (check_O(curr_line) && check_new_lines(curr_line, new_lines) && check_new_lines(curr_line, curr_line_vec))
	{
		curr_line_vec.push_back(curr_line);
		create_new_bound(CUR_P, TERM, -2, CUR_NUM);
		return true;
	}
	return false;
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

// Проверка пересечения с гранями объектов
bool GRAPH_CREATOR::check_O(LINE L_curr)
{
	for (int i = 0; i < O.size(); i++)
	{
		for (int j = 0; j < O[i].g_L().size(); j++)
		{
			LINE ob = O[i].g_L()[j];
			if (L_curr.intersect_segm_in_ob(ob)) 	return false;
		}
	}
	return true;
}

// Проверка пересечения с новыми линиями
bool GRAPH_CREATOR::check_new_lines(LINE L_curr, vector<LINE> VEC)
{
	for (int i = 0; i < VEC.size(); i++)
	{
		LINE ob = VEC[i];
		if (L_curr.intersect_segm_out(ob)) 	return false;
		if (L_curr.impos(ob)) return false;
	}
	return true;
}

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
		if (!already_nei(num, CUR_NUM))
		{
			LIST[num].add_neigh(CUR_NUM);
			LIST[num].add_weight(w);
		}

		if (!already_nei(CUR_NUM, num))
		{
			LIST[CUR_NUM].add_neigh(num);
			LIST[CUR_NUM].add_weight(w);
		}
	}
}

// Проверка на существование вершины
int GRAPH_CREATOR::already_exist(POINT P)
{
	for (int i = 0; i < LIST.size(); i++) if ((LIST[i].POINT_GR).equ(P)) return LIST[i].NUM;
	return -1;
}

// Проверка на существование соседства
bool GRAPH_CREATOR::already_nei(int n1, int n2)
{
	for (int i = 0; i < LIST[n1].g_nei().size(); i++) if (LIST[n1].g_nei()[i] == n2) return true;
	return false;
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