#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <string> 
#include <fstream>

using namespace std;

#include "Pont_Line.h"
#include "Obstruction.h" 
#include "Graph.h"

#define OBS_AMO 2

// ������� �������������� � ������� ����� � ������ ������
vector<double> read_data(string str);
POINT* vector_to_POINTS(vector<double> mas, int N);
OBS border_read();
vector<OBS> OBS_read();

vector<LINE> new_lines(vector<LINE> curr_line_vec, vector<LINE> new_lines, vector<OBS> O, int j, POINT P);
bool check_new_line(vector<LINE> curr_line_vec, vector<OBS> O, LINE L);