#include "Header.h"

// Вывод точек на печать
void OBS::print_points()
{
	for (int i = 0; i < N; i++) { cout << P[i].g_X() << " " << P[i].g_Y() << endl; }
} 

// Определение прямых, составляющих препятствие
void OBS::create_border(LINE* L)
{
	int i2 = 0;
	for (int i1 = 0; i1 < N; i1++)
	{
		i2 = (i1 != N - 1) ? (i1 + 1) : 0;
		LINE L_curr = L_curr.create_line(P[i1], P[i2]);
		L[i1] = L_curr;
	}
}

// Вывод коэффициентов линий на печать
void OBS::print_lines()
{
	for (int i = 0; i < N; i++) { cout << L[i].g_A() << " " << L[i].g_B() << " " << L[i].g_C() << endl; }
}

