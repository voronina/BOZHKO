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

/*class JSON_point {
private:
	double x, y;
	vector<POINT> CC;
public:
	JSON_point(double new_x, double new_y) : x(new_x), y(new_y) {};
};*/


/*class JSON_line {
private:

public:
void print() {

picojson::object v1;

double x1 = 10.9;
double y1 = 9.9;

v1["x1"] = picojson::value(x1);
v1["y1"] = picojson::value(y1);

picojson::object v2;

double x2 = 100.9;
double y2 = 90.9;

v2["x1"] = picojson::value(x2);
v2["y1"] = picojson::value(y2);

picojson::array arr;
arr.push_back(picojson::value(v1));
arr.push_back(picojson::value(v2));

string str = picojson::value(arr).serialize();
cout << str << endl;
}
};

class JSON_printer {
public:
void print() {

picojson::object v1;

double x1 = 10.9;
double y1 = 9.9;

v1["x1"] = picojson::value(x1);
v1["y1"] = picojson::value(y1);

picojson::object v2;

double x2 = 100.9;
double y2 = 90.9;

v2["x1"] = picojson::value(x2);
v2["y1"] = picojson::value(y2);

picojson::array arr;
arr.push_back(picojson::value(v1));
arr.push_back(picojson::value(v2));

string str = picojson::value(arr).serialize();
cout << str << endl;
}
};*/