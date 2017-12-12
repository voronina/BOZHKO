#include "Header.h"

int main()
{
	SourceData data = json_reader();

	// ��������� � �������� �����
	POINT ST = data.startPoint;
	POINT TERM = data.endPoint;
	cout << "START: " << ST.g_X() << " " << ST.g_Y() << endl;
	cout << "FINISH: " << TERM.g_X() << " " << TERM.g_Y() << endl;

	// ������������� ������ � �����������
	OBS B = border_create(ST, TERM);
	B.obs_print(-1);
	vector<OBS> O = data.polygons;
	for (int i = 0; i < O.size(); i++) O[i].obs_print(i);

	/*LINE L1(POINT(2, 0), POINT(2, 4));
	LINE L2(POINT(2, 4), POINT(3, 4));
	POINT PP(0,3);
	cout << endl << "ANS = " << L1.intersect_segm(L2) << endl;

	POINT PP(2, 5);
		cout << endl << "ANS = " << O[1].inside_border(PP) << endl;*/



	GRAPH_CREATOR GR_CREATOR(ST, TERM, O, B);
	GR_CREATOR.graph_creator();
	/*vector<VERTEX> LIST = GR_CREATOR.g_LIST();

	int TERM_NUM = LIST.size();
	for (int i = 0; i < LIST.size(); i++) if (LIST[i].g_O_NUM() == -2) TERM_NUM = i;

	double MAX_WEI = GR_CREATOR.find_weight(B.g_P()[0], B.g_P()[2]) + 1000;
	DIJKSTRA DIJ(LIST, MAX_WEI, TERM_NUM);

	vector<int> PATH = DIJ.algo();

	cout << endl << "PATH = " << endl;
	for (int i = PATH.size() - 1; i >= 0; i--) cout << PATH[i] << " ";
	cout << endl;*/

	system("pause");
	return 0; 
}

