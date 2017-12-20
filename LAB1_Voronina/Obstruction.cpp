#include "Header.h"

// Вывод точек на печать
void OBS::print_points()
{
	for (int i = 0; i < N; i++) { cout << P[i].g_X() << " " << P[i].g_Y() << endl; }
	cout << endl;
} 

// Определение прямых, составляющих препятствие
void OBS::create_border()
{
	int i2 = 0;
	for (int i1 = 0; i1 < N; i1++)
	{
		i2 = (i1 != N - 1) ? (i1 + 1) : 0;
		LINE L_curr(P[i1], P[i2]);
		L.push_back(L_curr);
	}
}

// Проверка на принадлежность области
bool OBS::inside_border(POINT P_in)
{
	for (int i = 0; i < P.size(); i++) if (P_in.equ(P[i])) return false;
	
	POINT mid_p = L[0].middle();
	
	LINE BEAM(P_in, mid_p);
	int bor_counter = 0;
	int bor_counter_help = 0;
	for (int i = 0; i < L.size(); i++)
	{
		if ( BEAM.intersect_beam(L[i]) ) bor_counter++; 
		for (int i = 0; i < P.size(); i++) if (P_in.equ(P[i])) // !!!!
		{
			bor_counter--;
			bor_counter_help++;
		}
	}
	bor_counter = bor_counter + bor_counter_help / 2;

	if (bor_counter % 2 == 1)  return true;

	for (int i = 0; i < L.size(); i++) if (L[i].contain(P_in)) return true;

	return false;
}

// Вывод коэффициентов линий на печать
void OBS::print_lines()
{
	for (int i = 0; i < N; i++) { cout << L[i].g_A() << " " << L[i].g_B() << " " << L[i].g_C() << endl; }
	cout << endl;
}

