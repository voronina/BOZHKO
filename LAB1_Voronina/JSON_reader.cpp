#include "Header.h"

SourceData json_reader()
{
	ifstream file("data_test.txt");

	picojson::value v;
	picojson::parse(v, file);

	SourceData data = SourceDataParser(v).parse();

	return data;
}

OBS border_create(POINT ST, POINT TERM)
{
	vector<POINT> P_vec;

	double delta = 1.0;
	double min_X = 0.0;
	double max_X = 0.0;
	double min_Y = 0.0;
	double max_Y = 0.0;

	// Получние граничных значений по Х
	if (ST.g_X() <= TERM.g_X())
	{
		//min_X = ST.g_X();
		max_X = TERM.g_X();
	}
	else
	{
		//min_X = TERM.g_X();
		max_X = ST.g_X();
	}

	// Получние граничных значений по Y
	if (ST.g_Y() <= TERM.g_Y())
	{
		//min_Y = ST.g_Y();
		max_Y = TERM.g_Y();
	}
	else
	{
		//min_Y = TERM.g_Y();
		max_Y = ST.g_Y();
	}

	//Создание границ
	P_vec.push_back(POINT((min_X), (min_Y)));
	P_vec.push_back(POINT((max_X + delta), (min_Y)));
	P_vec.push_back(POINT((max_X + delta), (max_Y + delta)));
	P_vec.push_back(POINT((min_X), (max_Y + delta)));

	LINE L_m(P_vec[0], P_vec[2]);
	POINT P_m = L_m.middle();

	return OBS(P_m, P_vec);
}