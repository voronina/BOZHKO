#include "Header.h"

int main()
{
	vector<double> read_inputs();

	vector<double> init_mas = read_inputs();
	int N = init_mas.size();

	//for (int i = 0; i < N; i++) { cout << init_mas[i] << endl; }

	// Создание вектора точек
	POINT* points = (POINT *)malloc(N * sizeof(POINT));
	for (int i = 0; i < N; i += 2)
	{
		POINT P(init_mas[i], init_mas[i + 1]);
		points[i / 2] = P;
	}

	// Создание препятствия
	OBS O(points, N/2);
	O.print_points();
	O.print_lines();
	O.obs_inersect();
	//O.obs_belong();


	system("pause");
	return 0; 
}

vector<double> read_inputs()
{
	vector<double> init_mas;

	ifstream inp("Inputs.txt");

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