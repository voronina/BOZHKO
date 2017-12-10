#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <picojson.h>

using namespace std;

class Point {
public:
	double x;
	double y;

	Point(double x, double y) : x(x), y(y) {};
};

class Polygon {
public:
	Point center;
	vector<Point> vertices;

	Polygon(Point p, vector<Point> vertices) : center(p), vertices(vertices) {};
};

class SourceData {
public:
	Point startPoint;
	Point endPoint;
	vector<Polygon> polygons;

	SourceData(Point startPoint, Point endPoint, vector<Polygon> polygons) : startPoint(startPoint), endPoint(endPoint), polygons(polygons) {};
};

class PointParser {
private:
	picojson::value & v;

	const string X = "x";
	const string Y = "y";

public:
	PointParser(picojson::value & v) : v(v) {};

	Point parse() 
	{
		return Point(
			v.get(X).get<double>(),
			v.get(Y).get<double>());
	};
};

class PolygonParser {
private:
	picojson::value & v;

	const string VERTICES = "vertices";

	vector<Point> parseVertices() 
	{
		vector<Point> vertices;
		auto verticesJson = v.get(VERTICES).get<picojson::array>();
		for (int i = 0; i < verticesJson.size(); ++i) {
			Point p = PointParser(verticesJson[i]).parse();
			vertices.push_back(p);
		}
		return vertices;
	};

public:
	PolygonParser(picojson::value & v) : v(v) {};

	Polygon parse() 
	{
		Point center = PointParser(v).parse();
		vector<Point> verices = parseVertices();
		return Polygon(center, verices);
	};
};

class SourceDataParser {
private:
	picojson::value & v;

	const string START_POINT = "start_point";
	const string END_POINT = "end_point";
	const string POLYGONS = "polygons";

	vector<Polygon> parsePolygons() 
	{
		vector<Polygon> polygons;
		auto polygonsJson = v.get(POLYGONS).get<picojson::array>();
		for (int i = 0; i < polygonsJson.size(); ++i) 
		{
			Polygon p = PolygonParser(polygonsJson[i]).parse();
			polygons.push_back(p);
		}
		return polygons;
	};


public:
	SourceDataParser(picojson::value & v) : v(v) {};

	SourceData parse() 
	{
		Point startPoint = PointParser(v.get(START_POINT)).parse();
		Point endPoint = PointParser(v.get(END_POINT)).parse();
		return SourceData(startPoint, endPoint, parsePolygons());
	};

};

void json_reader();