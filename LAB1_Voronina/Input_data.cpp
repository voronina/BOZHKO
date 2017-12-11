#include "Header.h"

// Чтение параметров препятствий
vector<OBS> OBS_read()
{
	// Адрес расположения исходных данных
	string str1 = ".\\INPUTS\\OBS_"; 		
	string str3 = ".txt";
	string str2, str4;

	POINT Y(0, 0);

	vector<OBS> O;

	vector<double> init_mas;
	vector<POINT> points;
	int N = 0;

	int k = 1;
	while( k <= OBS_AMO)
	{
		str2 = to_string(k);
		str4 = str1 + str2 + str3;

		init_mas = read_data(str4);
		N = init_mas.size();
		points = vector_to_POINTS(init_mas, N);

		OBS O_curr(Y, points);
		O.push_back(O_curr);

		cout << "Obstruction " << k << endl;
		O_curr.print_points();

		k++;
	}

	return O;
}

// Чтение параметров границ
OBS border_read()
{
	POINT Y(0, 0);

	// Чтение границ области видимости
	string str = ".\\INPUTS\\Borders.txt";
	vector<double> border_vec = read_data(str);
	int N_B = border_vec.size();
	vector<POINT> border = vector_to_POINTS(border_vec, N_B);
	OBS B(Y, border);

	cout << "Borders" << endl;
	B.print_points();

	return B;
}

// Создание вектора точек
vector<POINT> vector_to_POINTS(vector<double> init_mas, int N)
{
	vector<POINT> points; 

	for (int i = 0; i < N; i += 2)
	{
		POINT P(init_mas[i], init_mas[i + 1]);
		points.push_back(P);
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


// Инициализация границ и препятствий
/*OBS B = border_read();
vector<OBS> O = OBS_read();

// Стартовая и конечная точки
POINT ST(1,1);
POINT TERM(9,9);
cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

O.push_back(B);*/