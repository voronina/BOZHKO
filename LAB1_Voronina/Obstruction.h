// Класс препятствия (может использоваться как граница области определения)
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

	int g_N() { return N; };
	POINT* g_P() { return P; };
	LINE* g_L() { return L; };

	void create_border(LINE*);
	bool inside_border(POINT P);

	void print_points();
	void print_lines();

	/*void obs_inersect()
	{	POINT inter_point(0, 0);
	bool ans = L[0].intersect(L[1], L[3], inter_point);
	ans = ans * L[0].belong(inter_point);
	ans = ans * L[3].belong(inter_point);
	cout << ans << endl; };

	void obs_belong()
	{	POINT inter_point(1, 2);
	cout << L[0].belong(inter_point); };

	void obs_middle()
	{	POINT test = L[0].middle();
	cout << test.g_X() << " " << test.g_Y() << endl;	};*/
};
