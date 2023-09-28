#include "esperimento.hpp"

int main(int argc, const char** argv){

    if(argc != 2){
        fmt::print(stderr, "Errore! Uso del programma: {0} <n_volte>\n", argv[0]);
        exit(-1);
    }

    int n_volte{atoi(argv[1])};

    Glicerina nitro;

    nitro.Analizza(n_volte, 0.005);
    nitro.Analizza(n_volte, 0.005, 0, 0);
    nitro.Analizza(n_volte, 0.005, 0, 0.001, 0);
    nitro.Analizza(n_volte, 0.005, 0.01, 0, 0);
    nitro.Analizza(n_volte, 0.01);
    nitro.Analizza(n_volte, 0.01, 0, 0);
    nitro.Analizza(n_volte, 0.01, 0, 0.001, 0);
    nitro.Analizza(n_volte, 0.01, 0.01, 0, 0);

    return 0;
}