#include "Header.h"

// Чтение параметров препятствий
OBS* OBS_read()
{
	// Адрес расположения исходных данных
	string str1 = ".\\INPUTS\\OBS_"; 		
	string str3 = ".txt";
	string str2, str4;

	OBS* O = (OBS*)malloc(OBS_AMO*(sizeof(OBS))); // Массив препятствий

	vector<double> init_mas;
	POINT* points;
	int N = 0;

	int k = 1;
	while( k <= OBS_AMO)
	{
		str2 = to_string(k);
		str4 = str1 + str2 + str3;

		init_mas = read_data(str4);
		N = init_mas.size();
		points = vector_to_POINTS(init_mas, N);

		OBS O_curr(points, N/2);
		O[k-1] = O_curr;

		cout << "Obstruction " << k << endl;
		O_curr.print_points();

		k++;
	}

	return O;
}

// Чтение параметров границ
OBS border_read()
{
	// Чтение границ области видимости
	string str = ".\\INPUTS\\Borders.txt";
	vector<double> border_vec = read_data(str);
	int N_B = border_vec.size();
	POINT* border = vector_to_POINTS(border_vec, N_B);
	OBS B(border, N_B / 2);

	cout << "Borders" << endl;
	B.print_points();

	return B;
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