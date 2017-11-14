// Класс точки
class POINT {
private:
	double X;
	double Y;
public:
	POINT(double new_X, double new_Y) : X(new_X), Y(new_Y) {};

	double g_X() { return X; };
	double g_Y() { return Y; };
};

// Класс линии
class LINE {
private:
	double A, B, C;
public:
	LINE(double new_A, double new_B, double new_C) : A(new_A), B(new_B), C(new_C) {};

	double g_A() { return A; };
	double g_B() { return B; };
	double g_C() { return C; };

	LINE create_line(POINT P1, POINT P2);
	double det(double a, double b, double c, double d);
	bool intersect(LINE m, LINE n, POINT & res);
	bool equivalent(LINE m, LINE n);
	bool belong(POINT P);
};