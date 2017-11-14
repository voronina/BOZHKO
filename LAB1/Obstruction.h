// Класс препятствия
class OBS {
private:
	int N;
	POINT* P;
	LINE* L;
public:
	OBS(POINT* new_P, int new_N) : P(new_P), N(new_N) 
	{
		L = (LINE *)malloc(N * sizeof(LINE));
		create_border(L);
	};

	void obs_inersect()
	{
		POINT inter_point(0, 0);
		cout << L[0].intersect(L[0], L[3], inter_point) << endl;
	};

	/*void obs_belong()
	{
		POINT inter_point(1, 2);
		cout << L[0].belong(inter_point);
	};*/

	void create_border(LINE*);
	void print_points();
	void print_lines();
};
