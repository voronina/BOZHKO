#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <ostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <time.h>
#include <math.h>
#include <string> 

#include <picojson.h>

using namespace std;

#include "Pont_Line.h"
#include "Obstruction.h" 

#include "JSON_reader.h"

#include "Graph.h"
#include "Dijkstra.h"

// Функции преобразования к вектору точек и чтения данных
vector<double> read_data(string str);
vector<POINT> vector_to_POINTS(vector<double> mas, int N);
OBS border_read();
vector<OBS> OBS_read();