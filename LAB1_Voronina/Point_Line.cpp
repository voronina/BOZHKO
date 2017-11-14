#include "Header.h"
#define EPS 0.0001

// �������� �����
LINE LINE::create_line(POINT P1, POINT P2)
{
	double a_curr, b_curr, c_curr;

	a_curr = P1.g_Y() - P2.g_Y();
	b_curr = P2.g_X() - P1.g_X();
	c_curr = P1.g_X() * P2.g_Y() - P2.g_X() * P1.g_Y();
	LINE L_curr(a_curr, b_curr, c_curr, P1, P2);

	return L_curr;

}

// �����������
double LINE::det(double a, double b, double c, double d) { return a * d - b * c; }

// �������� �� ����������� �����
bool LINE::intersect(LINE L1, LINE L2, POINT &res)
{
	double x, y;
	double zn = det(L1.g_A(), L1.g_B(), L2.g_A(), L2.g_B());
	if (abs(zn) < EPS)	return false;
	x = -det(L1.g_C(), L1.g_B(), L2.g_C(), L2.g_B()) / zn;
	y = -det(L1.g_A(), L1.g_C(), L2.g_A(), L2.g_C()) / zn;
	POINT curr_res(x, y);
	res = curr_res;
	return true;
}

// �������� �� ��������������� �����
bool LINE::equivalent(LINE L1, LINE L2)
{
	return abs(det(L1.g_A(), L1.g_B(), L2.g_A(), L2.g_B())) < EPS
		&& abs(det(L1.g_A(), L1.g_C(), L2.g_A(), L2.g_C())) < EPS
		&& abs(det(L1.g_B(), L1.g_C(), L2.g_B(), L2.g_C())) < EPS;
}

// �������� �� �������������� ����
bool LINE::belong(POINT P)
{
	double min_X, max_X, min_Y, max_Y;

	double res = A * P.g_X() + B * P.g_Y() + C;

	if (P1.g_X() < P2.g_X()) { min_X = P1.g_X(); max_X = P2.g_X(); }
	else { min_X = P2.g_X(); max_X = P1.g_X(); }

	if (P1.g_Y() < P2.g_Y()) { min_Y = P1.g_Y(); max_Y = P2.g_Y(); }
	else { min_Y = P2.g_Y(); max_Y = P1.g_Y(); }

	if ( min_X <= P.g_X() && max_X >= P.g_X() && min_Y <= P.g_Y() && max_Y >= P.g_Y() && res == 0 ) return true;
	return false;
}


// �������� �������
POINT LINE::middle()
{
	double X = ( P1.g_X() + P2.g_X() ) / 2;
	double Y = ( P1.g_Y() + P2.g_Y() ) / 2;
	POINT curr_P(X, Y);
	return curr_P;
}
