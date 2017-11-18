class GRAPH;

class VERTEX {
private:
	int NUM;
	int O_NUM;
	POINT POINT_GR;
	vector<int> neigh;
public:
	VERTEX(int new_NUM, int new_O_NUM, POINT new_P) : NUM(new_NUM), O_NUM(new_O_NUM), POINT_GR(new_P){};
	friend GRAPH;
};

class GRAPH {
private:
	int NUM_VER;	
	vector<VERTEX> LIST;
	vector<VERTEX> OPEN;
	vector<VERTEX> CLOSE;
	POINT TERM;

public:
	GRAPH(POINT ST, POINT new_TERM) : TERM(new_TERM)
	{
		VERTEX NEW_V(0, -1, ST);
		CLOSE.push_back(NEW_V);
		LIST.push_back(NEW_V);
		NUM_VER = 1;
	};

	vector<LINE> create_lines(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, int j, POINT P);
	bool check_new_line(vector<LINE> curr_line_vec, vector<OBS> O, LINE L);
	vector<LINE> create_line_to_term(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, POINT CUR_P, POINT T);

	void graph_creator(vector<OBS> O);
};