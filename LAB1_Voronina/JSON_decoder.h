class SourceData {
public:
	POINT startPoint;
	POINT endPoint;
	vector<OBS> polygons;

	SourceData(POINT startPoint, POINT endPoint, vector<OBS> polygons) : startPoint(startPoint), endPoint(endPoint), polygons(polygons) {};
};

class PointParser {
private:
	picojson::value & v;

	const string X = "x";
	const string Y = "y";

public:
	PointParser(picojson::value & v) : v(v) {};

	POINT parse() 
	{
		return POINT(
			v.get(X).get<double>(),
			v.get(Y).get<double>());
	};
};

class PolygonParser {
private:
	picojson::value & v;

	const string VERTICES = "vertices";

	vector<POINT> parseVertices() 
	{
		vector<POINT> vertices;
		auto verticesJson = v.get(VERTICES).get<picojson::array>();
		for (int i = 0; i < verticesJson.size(); ++i) {
			POINT p = PointParser(verticesJson[i]).parse();
			vertices.push_back(p);
		}
		return vertices;
	};

public:
	PolygonParser(picojson::value & v) : v(v) {};

	OBS parse() 
	{
		POINT center = PointParser(v).parse();
		vector<POINT> verices = parseVertices();
		return OBS(center, verices);
	};
};

class SourceDataParser {
private:
	picojson::value & v;

	const string START_POINT = "start";
	const string END_POINT = "finish";
	const string POLYGONS = "polygons";

	vector<OBS> parsePolygons() 
	{
		vector<OBS> polygons;
		auto polygonsJson = v.get(POLYGONS).get<picojson::array>();
		for (int i = 0; i < polygonsJson.size(); ++i) 
		{
			OBS p = PolygonParser(polygonsJson[i]).parse();
			polygons.push_back(p);
		}
		return polygons;
	};


public:
	SourceDataParser(picojson::value & v) : v(v) {};

	SourceData parse() 
	{
		POINT startPoint = PointParser(v.get(START_POINT)).parse();
		POINT endPoint = PointParser(v.get(END_POINT)).parse();
		return SourceData(startPoint, endPoint, parsePolygons());
	};

};

SourceData json_reader();
OBS border_create(POINT ST, POINT TERM);


/**********************************************************************************************/

class JSON_line {
public:
	picojson::object L;
	JSON_line(POINT B, POINT E)
	{
		L["x1"] = picojson::value(B.g_X());
		L["y1"] = picojson::value(B.g_Y());
		L["x2"] = picojson::value(E.g_X());
		L["y2"] = picojson::value(E.g_Y());
	};
};

class JSON_writer {
public:
	picojson::array LINES;
	JSON_writer(vector<POINT> P)
	{
		for (int i = 0; i < P.size() - 1; i++) LINES.push_back(picojson::value(JSON_line(P[i], P[i + 1]).L));
	};

	void write_JSON(void)
	{
		string str = picojson::value(LINES).serialize();
		//cout << str << endl;

		ofstream fout;
		fout.open("output_json.txt");
		fout << str << endl;
		fout.close();
	};
};