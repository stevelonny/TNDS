#include <iostream>
#include <fstream>
#include <cmath>
#include "vettore.h"

using namespace std;

double Media(const Vettore vett);
double Var(Vettore data);
double Devstd(Vettore data);
Vettore Leggi(const char* filename, int ndata);
//void Stampa(const char * filename, double data[], int dim);
void Stampa(Vettore data, int dim);
double * CopiaDaClasse(const Vettore vett);
void Ordina(Vettore data);
double Mediana(double data[], int dim);
void Scrivi(const char * filename, double data[], int dim);