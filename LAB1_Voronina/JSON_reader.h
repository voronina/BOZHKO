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

	const string START_POINT = "start_point";
	const string END_POINT = "end_point";
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