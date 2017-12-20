#include "Header.h"

int main()
{
	// ������ ������ �� �����
	SourceData data = json_reader();

	// ��������� � �������� �����
	POINT ST = data.startPoint;
	POINT TERM = data.endPoint;
	cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
	cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

	cout << "SOLUTION IN WORK..." << endl;
	unsigned int start_time = clock();

	// ������������� ������ � �����������
	OBS B = border_create(ST, TERM);
	//B.obs_print(-1);										// ������ ����� ������
	vector<OBS> O = data.polygons;
	//for (int i = 0; i < O.size(); i++) O[i].obs_print(i);	// ������ ������ ��������

	// ���������� �����
	GRAPH_CREATOR GR_CREATOR(ST, TERM, O, B);
	bool ans = GR_CREATOR.graph_creator();
	//GR_CREATOR.print_LIST();								// ������ ���������� � �����
	
	// ���������� ���� �� ����� (���� �� ����)
	if (ans)
	{
		// ����� ����������� ���� ������� ��������
		double MAX_WEI = GR_CREATOR.find_weight(B.g_P()[0], B.g_P()[2]) + 1000;
		DIJKSTRA DIJ(GR_CREATOR.g_LIST(), MAX_WEI);
		vector<POINT> PATH = DIJ.algo();
		DIJ.print_path();									// ������ ����
		JSON_writer(PATH).write_JSON();
	}
	else
	{
		cout << endl << "THERE IS NO WAY!" << endl;
	}

	unsigned int end_time = clock();
	cout << endl << "END OF SOLUTION!" << endl << endl;
	cout << "TIME:" << (end_time - start_time)/1000.0 << endl << endl;
	
	system("pause");
	return 0; 
}

