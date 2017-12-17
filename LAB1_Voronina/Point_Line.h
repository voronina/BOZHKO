// Класс точки
class POINT {
private:
	double X;
	double Y;
public:
	POINT(double new_X, double new_Y) : X(new_X), Y(new_Y) {};

	double g_X() { return X; };
	double g_Y() { return Y; };

	void zero_point() { X = 0; Y = 0; };
	void print_point() { cout <<  X << " " << Y << endl; };

	bool equivalent(POINT P);
};

// Класс линии
class LINE {
private:
	double A, B, C;
	POINT P1, P2;
public:
	LINE(POINT new_P1, POINT new_P2) : P1(new_P1), P2(new_P2)
	{
		A = P1.g_Y() - P2.g_Y();
		B = P2.g_X() - P1.g_X();
		C = P1.g_X() * P2.g_Y() - P2.g_X() * P1.g_Y();
	};

	double g_A() { return A; };
	double g_B() { return B; };
	double g_C() { return C; };

	POINT g_P1() { return P1; };
	POINT g_P2() { return P2; };

	void print_line() {  P1.print_point();   P2.print_point(); 	};

	double det(double a, double b, double c, double d);

	bool contain(POINT P);
	bool contain_out(POINT P);
	POINT middle();

	bool equivalent_line(LINE L);
	bool equivalent_segm(LINE L);

	double zn(LINE L);
	double x_sol(LINE L, double zn);
	double y_sol(LINE L, double zn);

	bool intersect_segm(LINE L);
	bool intersect_segm_without_P(LINE L);
	bool intersect_beam(LINE L);
	bool impos(LINE L); 
	bool on_beam(LINE L);
};