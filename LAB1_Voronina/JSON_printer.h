#include <picojson.h>
#include <iostream>

using namespace std;

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
};