#include "montecarlo.hpp"
#include "../fmtlib.h"

using namespace std;

int main(int argc, const char** argv){

    if(argc!=2){
        fmt::print("Troppi pochi argomenti! Uso del programma: {0} <n_punti>\n", argv[0]);
        exit(-1);
    }

    MonteCarlo sium(1);
    Seno sen;
    double res{sium.Media(sen, 0., M_PI, (unsigned int)atoi(argv[1]))};
    double err{sium.GetError()};
    int points{sium.GetN()};
    fmt::print("Metodo MonteCarlo con media tra 0 e pi: {0}\n", res);
    fmt::print("Con {0} punti utilizzati\n", points);
    MonteCarlo muis(1);
    res = muis.Hit(sen, 0., M_PI, (unsigned int)atoi(argv[1]), 1.);
    points = muis.GetN();
    fmt::print("Metodo MonteCarlo con Hit or Miss tra 0 e pi: {0}\n", res);
    fmt::print("Con un rapporto HoM {0} / {1} punti \n", points, muis.GetMAX());

    return 0;
}