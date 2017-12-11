#include "Header.h"

// ����� ����� �� ������
void OBS::print_points()
{
	for (int i = 0; i < N; i++) { cout << P[i].g_X() << " " << P[i].g_Y() << endl; }
	cout << endl;
} 

// ����������� ������, ������������ �����������
void OBS::create_border()
{
	int i2 = 0;
	for (int i1 = 0; i1 < N; i1++)
	{
		i2 = (i1 != N - 1) ? (i1 + 1) : 0;
		LINE L_curr = L_curr.create_line(P[i1], P[i2]);
		L.push_back(L_curr);
	}
}

// �������� �� �������������� �������
bool OBS::inside_border(POINT P_in)
{
	for (int i = 0; i < P.size(); i++) if (P_in.equivalent(P[i])) return false;
	
	POINT mid_p = L[0].middle();
	POINT inter_point(0, 0);
	
	LINE BEAM = BEAM.create_line(P_in, mid_p);
	int bor_counter = 0;
	int bor_counter_help = 0;
	for (int i = 0; i < L.size(); i++)
	{
		if (BEAM.intersect_line(BEAM, L[i], inter_point))  bor_counter++; 
		for (int i = 0; i < P.size(); i++) if (P_in.equivalent(P[i]))
		{
			bor_counter--;
			bor_counter_help++;
		}
	}
	bor_counter = bor_counter + bor_counter_help / 2;

	if (bor_counter % 2 == 1)  return true;

	for (int i = 0; i < L.size(); i++) if (L[i].belong(P_in)) return true;

	return false;
}

// ����� ������������� ����� �� ������
void OBS::print_lines()
{
	for (int i = 0; i < N; i++) { cout << L[i].g_A() << " " << L[i].g_B() << " " << L[i].g_C() << endl; }
	cout << endl;
}

