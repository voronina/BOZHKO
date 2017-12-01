class GRAPH_CREATOR;

// Класс вершины графа
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
	void add_weight(int NEI_W) { weight.push_back(NEI_W); };

	void print_vertex();

	int g_O_NUM() { return O_NUM; };
	int g_PAR() { return PARENT; };

	friend GRAPH_CREATOR;
};


// Класс создания графа
class GRAPH_CREATOR {
private:
	int NUM_VER;	
	vector<VERTEX> LIST;
	vector<int> OPEN;
	vector<int> CLOSE;
	POINT TERM;

	vector<LINE> curr_line_vec, new_lines;
	vector<OBS> O;

public:
	GRAPH_CREATOR(POINT ST, POINT new_TERM, vector<OBS> new_O) : TERM(new_TERM), O(new_O)
	{
		VERTEX NEW_V(0, -1, ST, -1);
		LIST.push_back(NEW_V);
		OPEN.push_back(0);
		NUM_VER = 1;
	};

	void graph_creator(int P_AMO);

	vector<LINE> create_lines(int j, int CUR_NUM, POINT P);
	vector<LINE> create_line_to_term(POINT CUR_P, int CUR_NUM, POINT T);
	vector<LINE> create_into_obs(int j, int CUR_NUM, POINT P);
	bool check_new_line(LINE L, int flag_obs);
	
	void all_new_lines(int CUR_NUM);

	void create_new_bound(POINT P1, POINT P2, int j, int CUR_NUM);
	int already_exist(POINT P);
	double find_weight(POINT P1, POINT P2);

	vector<VERTEX> g_LIST() { return LIST;  };

	void print_open_close()
	{
		cout << endl << "NEW_L.size() = " << new_lines.size();
		if (OPEN.size() > 0) cout << endl << "OPEN = ";  for (int i = 0; i < OPEN.size(); i++) cout << OPEN[i] << "; ";
		if (CLOSE.size() > 0) cout << endl << "CLOSE = ";  for (int i = 0; i < CLOSE.size(); i++) cout << CLOSE[i] << "; ";
		cout << endl << endl;
	};
};