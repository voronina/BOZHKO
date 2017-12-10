#include "Header.h"

void json_reader() 
{
	ifstream file("C:\\Users\\Полина\\Desktop\\BOZHKO\\BOZHKO\\LAB1_Voronina\\data.txt");

	picojson::value v;
	picojson::parse(v, file);

	SourceData data = SourceDataParser(v).parse();

	// print first polygon's first vertex.
	auto p1 = data.polygons[0].vertices[2];
	cout << p1.x << ":" << p1.y << endl;

	getchar();

}