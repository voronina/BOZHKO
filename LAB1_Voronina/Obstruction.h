// ����� ����������� (����� �������������� ��� ������� ������� �����������)
class OBS {
private:
	int N;
	POINT center;
	vector<POINT> P;
	vector<LINE> L;
public:
	OBS(POINT new_center, vector<POINT> new_P) : center(new_center), P(new_P)
	{
		N = P.size();
		create_border();
	};

	int g_N() { return N; };
	vector<POINT> g_P() { return P; };
	vector<LINE> g_L() { return L; };

	void create_border();
	bool inside_border(POINT P);

	void print_points();
	void print_lines();

	void obs_inersect(LINE L1, LINE L2)
	{	
		POINT inter_point(0, 0);
		bool ans = L1.intersect(L1, L2, inter_point);
		cout << "TEST = " << ans << endl;
	};

	void obs_print(int a)
	{
		if (a >= 0)	cout << endl << "Obctruction # " << a << endl;
		if (a < 0)	cout << endl << "Border" << endl;
		for (int i = 0; i < P.size(); i++)
		{
			P[i].print_point();
		}
	};
};
