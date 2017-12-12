#include "Header.h"
#define EPS 0.000001

// Эквивалентность точек
bool POINT::equivalent(POINT P)
{
	if (X != P.g_X()) return false;
	if (Y != P.g_Y()) return false;
	return true;
}

/*********************************************************************************/
// Детерминант
double LINE::det(double a, double b, double c, double d) { return a * d - b * c; }

// Проверка на эквивалентность линий
bool LINE::equivalent_line(LINE L)
{
	return abs(det(A, B, L.g_A(), L.g_B())) < EPS
		&& abs(det(A, C, L.g_A(), L.g_C())) < EPS
		&& abs(det(B, C, L.g_B(), L.g_C())) < EPS;
}

// Проверка на эквивалентность отрезков
bool LINE::equivalent_segm(LINE L)
{
	if ((P1.equivalent(L.g_P1()) && P2.equivalent(L.g_P2())) || 
		(P1.equivalent(L.g_P2()) && P2.equivalent(L.g_P1()))) return true;
	return false;
}

// Середина отрезка
POINT LINE::middle()
{
	double X = (P1.g_X() + P2.g_X()) / 2;
	double Y = (P1.g_Y() + P2.g_Y()) / 2;
	POINT curr_P(X, Y);
	return curr_P;
}

// Проверка на принадлежность отрезку
bool LINE::contain(POINT P)
{
	double min_X, max_X, min_Y, max_Y;

	double res = A * P.g_X() + B * P.g_Y() + C;

	if (P1.g_X() < P2.g_X()) { min_X = P1.g_X(); max_X = P2.g_X(); }
	else { min_X = P2.g_X(); max_X = P1.g_X(); }

	if (P1.g_Y() < P2.g_Y()) { min_Y = P1.g_Y(); max_Y = P2.g_Y(); }
	else { min_Y = P2.g_Y(); max_Y = P1.g_Y(); }

	if (min_X <= P.g_X() && max_X >= P.g_X() && min_Y <= P.g_Y() && max_Y >= P.g_Y() && abs(res) < EPS) return true;
	return false;
}

// Вспомогательные расчеты
double LINE::zn(LINE L) { return det(A, B, L.g_A(), L.g_B());}
double LINE::x_sol(LINE L, double zn) { return -det(C, B, L.g_C(), L.g_B()) / zn;}
double LINE::y_sol(LINE L, double zn) { return -det(A, C, L.g_A(), L.g_C()) / zn; }

// Проверка на пересечение отрезков
bool LINE::intersect_segm(LINE L)
{
	if (equivalent_segm(L)) return true;
	if(impos(L)) return true;
	if (abs(zn(L)) < EPS)	return false;
	POINT res = POINT(x_sol(L, zn(L)), y_sol(L, zn(L)));
	if (!contain(res) || !L.contain(res)) return false;
	return true;
}

// Проверка на пересечение отрезков
bool LINE::intersect_segm_without_P(LINE L)
{
	if (equivalent_segm(L)) return true; 
	if (abs(zn(L)) < EPS)	return false;
	POINT res = POINT(x_sol(L, zn(L)), y_sol(L, zn(L)));
	if (!contain(res) || !L.contain(res)) return false;
	if(res.equivalent(P1) || res.equivalent(P2)) return false;
	if (res.equivalent(L.g_P1()) || res.equivalent(L.g_P2())) return false;
	if (impos(L)) return true; 
	return true;
}

// Проверка на пересечение луча и отрезка
bool LINE::intersect_beam(LINE L)
{
	if (equivalent_segm(L)) return true;
	if (impos(L)) return true;
	if (on_beam(L)) return true;
	if (abs(zn(L)) < EPS)	return false;
	POINT res = POINT(x_sol(L, zn(L)), y_sol(L, zn(L)));
	if (!L.contain(res)) return false;
	if (contain(res) && L.contain(res)) return true;
	if (abs(A * res.g_X() + B * res.g_Y() + C) < EPS)
	{
		LINE L_test(P1, res);
		if (!L_test.contain(P2))  return false;
	}
	return true;
}

// Проверка частичного наложения
ПРОБЛЕМА
bool LINE::impos(LINE L)
{
	if (!equivalent_line(L)) return false;
	if (!contain(L.g_P1()) && !contain(L.g_P2()) && !L.contain(P1) && !L.contain(P2) ) return false;
	return true;
}

// Проверка принадлежности отрезка лучу
bool LINE::on_beam(LINE L)
{
	double X = P1.g_X();
	double Y = P1.g_Y();

	if (!equivalent_line(L)) return false;
	bool si_x = ( X >= P2.g_X()) ? true : false;
	bool si_y = ( Y >= P2.g_Y()) ? true : false;

	bool si_x_P1 = ( X >= L.g_P1().g_X()) ? true : false;
	bool si_y_P1 = ( Y >= L.g_P1().g_Y()) ? true : false;

	bool si_x_P2 = ( X >= L.g_P2().g_X()) ? true : false;
	bool si_y_P2 = ( Y >= L.g_P2().g_Y()) ? true : false;

	if( si_x && si_x_P1 && si_x_P2) return true;
	if( !si_x && !si_x_P1 && !si_x_P2) return true;

	if (si_y && si_y_P1 && si_y_P2) return true;
	if (!si_y && !si_y_P1 && !si_y_P2) return true;

	return false;
}
