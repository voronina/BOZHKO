#include "Header.h"

int main()
{
	POINT* vector_to_POINTS(vector<double> mas, int N);
	vector<double> read_data(string str);

	string str = ".\\INPUTS\\Borders.txt";

	vector<double> border_vec = read_data(str);
	int N_B = border_vec.size();
	POINT* border = vector_to_POINTS(border_vec, N_B);
	OBS B(border, N_B / 2);

	/*int k = 1;
	string str1 = ".\\INPUTS\\OBS_";
	string str3 = ".txt";
	string str2 = to_string(k);*/

	str = ".\\INPUTS\\OBS_1.txt";

	vector<double> init_mas = read_data(str);
	int N = init_mas.size();
	POINT* points = vector_to_POINTS(init_mas, N);

	POINT test_point(2, 0.5);

	// Создание препятствия
	OBS O(points, N/2);
	O.print_points();
	cout << O.inside_border(test_point) << endl;

	system("pause");
	return 0; 
}

// Создание вектора точек
POINT* vector_to_POINTS(vector<double> init_mas, int N)
{
	POINT* points = (POINT *)malloc(N * sizeof(POINT));
	for (int i = 0; i < N; i += 2)
	{
		POINT P(init_mas[i], init_mas[i + 1]);
		points[i / 2] = P;
	}
	return points;
}

vector<double> read_data(string str)
{
	vector<double> init_mas;

	ifstream inp(str);

	double input = 0;
	double* value = NULL;
	int i = 0;

	while (!inp.eof())
	{
		i++;
		inp >> input;
		init_mas.push_back(input);
	}
	inp.close();

	if (i % 2 != 0)
	{
		cout << "Wrong initial!" << endl;
		exit(1);
	}

	return init_mas;
}