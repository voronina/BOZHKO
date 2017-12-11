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
	LINE(double new_A, double new_B, double new_C, POINT new_P1, POINT new_P2) : A(new_A), B(new_B), C(new_C), P1(new_P1), P2(new_P2) {};

	double g_A() { return A; };
	double g_B() { return B; };
	double g_C() { return C; };

	POINT g_P1() { return P1; };
	POINT g_P2() { return P2; };

	void print_line() {  P1.print_point();   P2.print_point(); 	};

	LINE create_line(POINT P1, POINT P2);
	double det(double a, double b, double c, double d);
	bool intersect(LINE m, LINE n, POINT & res);
	bool intersect_line(LINE m, LINE n, POINT & res);
	bool equivalent(LINE m, LINE n);
	bool belong(POINT P);
	POINT middle();
};