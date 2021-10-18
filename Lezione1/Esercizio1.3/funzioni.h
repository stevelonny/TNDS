#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

double media(double data[],int dim);
double var(double data[], int dim);
double devstd(double data[],int dim);
double * leggi(const char* filename, int ndata);
void stampa(const char * filename, double data[], int dim);
void stampa(double data[], int dim);
double * copia(double data[], int dim);
void ordina(double vett[],int dim);
double mediana(double data[], int dim);
void scrivi(const char * filename, double data[], int dim);