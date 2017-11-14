#include "Header.h"
#define EPS 0.0001

// Создание линии
LINE LINE::create_line(POINT P1, POINT P2)
{
	double a_curr, b_curr, c_curr;

	a_curr = P1.g_Y() - P2.g_Y();
	b_curr = P2.g_X() - P1.g_X();
	c_curr = P1.g_X() * P2.g_Y() - P2.g_X() * P1.g_Y();
	LINE L_curr(a_curr, b_curr, c_curr);

	return L_curr;

}

// Детерминант
double LINE::det(double a, double b, double c, double d) { return a * d - b * c; }

// Проверка на пересечение линий
bool LINE::intersect(LINE m, LINE n, POINT &res)
{
	double x, y;
	double zn = det(m.g_A(), m.g_B(), n.g_A(), n.g_B());
	if (abs(zn) < EPS)	return false;
	x = -det(m.g_C(), m.g_B(), n.g_C(), n.g_B()) / zn;
	y = -det(m.g_A(), m.g_C(), n.g_A(), n.g_C()) / zn;
	POINT curr_res(x, y);
	res = curr_res;
	if ( !m.belong(curr_res) && !n.belong(curr_res) ) return false;
	return true;
}

// Проверка на эувивалентность линий
bool LINE::equivalent(LINE m, LINE n)
{
	return abs(det(m.g_A(), m.g_B(), n.g_A(), n.g_B())) < EPS
		&& abs(det(m.g_A(), m.g_C(), n.g_A(), n.g_C())) < EPS
		&& abs(det(m.g_B(), m.g_C(), n.g_B(), n.g_C())) < EPS;
}

// Проверка на принадлежность отрезку
bool LINE::belong(POINT P)
{
	double res = A * P.g_X() + B * P.g_Y() + C;
	if (res == 0) return true;
	return false;
}
