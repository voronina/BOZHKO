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
#include "Dijkstra.h"

#define OBS_AMO 2

// Функции преобразования к вектору точек и чтения данных
vector<double> read_data(string str);
POINT* vector_to_POINTS(vector<double> mas, int N);
OBS border_read();
vector<OBS> OBS_read();

