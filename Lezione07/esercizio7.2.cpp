#include "integratore.hpp"

#include "../fmtlib.h"

using namespace std;


int main(int argc, const char** argv){
    
    if(argc != 2){
        fmt::print(stderr, "Troppi pochi argomenti!\nUso del programma : {0} <prec>\n", argv[0]);
        exit(-1);
    }

    double prec=atof(argv[1]);
    //prec = 1e-3;
    Seno sen;
    Trapezoidi trap;
    double inte = trap.Integrate(0, M_PI, prec, sen);
    int cfr = round(-log10(trap.getPrecision())+0.5);
    fmt::print("Trovato valore di {0:.{1}f} con precisione {2:.0e} dopo {3} iterazioni\n",
                inte, cfr, trap.getPrecision(), trap.getIterations());
    //cout << inte << " " << trap.getIterations() << " " << trap.getPrecision();

    return 0;
}