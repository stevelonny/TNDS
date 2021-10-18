#include "vettore.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

double Mean(const Vettore vett);
double Variance(const Vettore data);
double StdDev(const Vettore data);
Vettore Read(const char* filename, int ndata);
//void Stampa(const char * filename, double data[], int dim);
void Print(const Vettore data, int dim);
double * CopyFromVettore(const Vettore vett);
void Sort(double * data, int ndata);
void Sort(Vettore vett);
double Median(const Vettore data);
void Write(const char * filename, Vettore data, int dim);