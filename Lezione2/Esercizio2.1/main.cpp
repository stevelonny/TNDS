#include "vettore.h"
#include "stats.h"

int main(int argc, const char *argv[]){
    int ndata = atoi(argv[1]);

    const char * filename = argv[2];

    Vettore data = Leggi(filename, ndata);

    Stampa(data, 10);

    ~data;

    return 1;

}