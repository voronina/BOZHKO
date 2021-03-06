class GRAPH_CREATOR;

// ����� ������� �����
class VERTEX {
private:
	int NUM;
	int PARENT;
	int O_NUM;
	POINT POINT_GR;
	vector<int> neigh;
	vector<double> weight;
public:
	VERTEX(int new_NUM, int new_O_NUM, POINT new_P, int new_PAR) : NUM(new_NUM), O_NUM(new_O_NUM), POINT_GR(new_P), PARENT(new_PAR) {};
	void add_neigh(int NEI_V) { neigh.push_back(NEI_V); };
	void add_weight(double NEI_W) { weight.push_back(NEI_W); };

	void print_vertex();

	int g_O_NUM() { return O_NUM; };
	POINT g_P() { return POINT_GR; };
	int g_PAR() { return PARENT; };
	vector<int> g_nei() { return  neigh; };
	vector<double> g_wei() { return  weight; };
	//int g_wei_i(int i) { return  weight[i]; };

	friend GRAPH_CREATOR;
};


// ����� �������� �����
class GRAPH_CREATOR {
private:
	int NUM_VER;	

	vector<OBS> O;
	OBS B;

	vector<VERTEX> LIST;
	vector<int> OPEN;
	vector<int> CLOSE;
	POINT TERM;

public:

	vector<LINE> curr_line_vec, new_lines;

	GRAPH_CREATOR(POINT ST, POINT new_TERM, vector<OBS> new_O, OBS new_B) : TERM(new_TERM), O(new_O), B(new_B)
	{
		VERTEX NEW_V(0, -1, ST, -1);
		LIST.push_back(NEW_V);
		OPEN.push_back(0);
		NUM_VER = 1;
	};
	
	bool graph_creator();
	bool on_free_space(POINT P);

	bool all_new_lines(int CUR_NUM);

	bool check_O(LINE L_curr);
	bool check_new_lines(LINE L_curr, vector<LINE> VEC);

	vector<LINE> create_lines(int j, int CUR_NUM, POINT P);
	
	void create_new_bound(POINT P1, POINT P2, int j, int CUR_NUM);
	int already_exist(POINT P);
	bool already_nei(int n1, int n2);
	double find_weight(POINT P1, POINT P2);

	vector<LINE> create_into_obs(int j, int CUR_NUM, POINT P);
	void L_inti_O(LINE L, int j, int CUR_NUM, POINT P);

	bool create_line_to_term(POINT CUR_P, int CUR_NUM);
	
	vector<VERTEX> g_LIST() { return LIST;  };

	void print_open_close()
	{
		cout << endl << "NEW_L.size() = " << new_lines.size();
		if (OPEN.size() > 0) cout << endl << "OPEN = ";  for (int i = 0; i < OPEN.size(); i++) cout << OPEN[i] << "; ";
		if (CLOSE.size() > 0) cout << endl << "CLOSE = ";  for (int i = 0; i < CLOSE.size(); i++) cout << CLOSE[i] << "; ";
		cout << endl << endl;
	};

	void print_LIST()
	{
		for (int i = 0; i < LIST.size(); i++) LIST[i].print_vertex();
	}

};