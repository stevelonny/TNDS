#include "vettore.h"
#include "stats.h"

int main(int argc, const char *argv[]){
    int ndata = atoi(argv[1]);

    const char * filename = argv[2];

    cout << ndata <<  endl;

    Vettore data = Leggi(filename, ndata);
    cout << endl;
    cout << data.GetN() << endl;
    cout << endl;

    Stampa(data, 10);

    return 1;

}