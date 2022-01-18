#include "esperimento.hpp"
#include "../fmtlib.h"


using namespace std;

int main(int argc, const char** argv){
    if(argc!=2){
        fmt::print(stderr, "Sintassi errata! Uso del programma: {0} <N_volte simulazione esperimento>\n", argv[0]);
        exit(-1);
    }

    EsperimentoPrisma prisma;
    
    fmt::print("Avvio simulazione di {0} istanze...\n", argv[1]);
    prisma.Analizza(atoi(argv[1]));

    return 0;

}