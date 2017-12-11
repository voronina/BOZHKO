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
		LINE L_curr = L_curr.create_line(P[i1], P[i2]);
		L.push_back(L_curr);
	}
}

// Проверка на принадлежность области
bool OBS::inside_border(POINT P)
{
	POINT mid_p = L[0].middle();
	POINT inter_point(0, 0);

	LINE BEAM = BEAM.create_line(P, mid_p);

	bool ans = 1;
	int bor_counter = 0;

	for (int i = 0; i < N; i++)
	{
		ans = ans * BEAM.intersect(BEAM, L[i], inter_point);
		ans = ans * BEAM.belong(inter_point);
		ans = ans * L[i].belong(inter_point);
		if (ans == 1) bor_counter ++;
		ans = 1;
	}

	if ( bor_counter % 2 == 1 ) return true;
	return false;
}

// Вывод коэффициентов линий на печать
void OBS::print_lines()
{
	for (int i = 0; i < N; i++) { cout << L[i].g_A() << " " << L[i].g_B() << " " << L[i].g_C() << endl; }
	cout << endl;
}

