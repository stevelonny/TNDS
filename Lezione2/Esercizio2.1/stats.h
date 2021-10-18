#include <iostream>
#include <fstream>
#include <cmath>
#include "vettore.h"

using namespace std;

double Media(const Vettore vett);
double Var(double data[], int dim);
double Devstd(double data[],int dim);
double * Leggi(const char* filename, int ndata);
//void Stampa(const char * filename, double data[], int dim);
void Stampa(double data[], int dim);
double * CopiaDaClasse(const Vettore vett);
void Ordina(double vett[],int dim);
double Mediana(double data[], int dim);
void Scrivi(const char * filename, double data[], int dim);