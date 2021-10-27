#include "particella.hpp"

int main(int argc, char** argv){
    if(argc!=3){
        cerr << "Uso del programma: " << argv[0] << " massa carica" << endl;
        exit(-1);
    }

    double m = atof(argv[1]);
    double c = atof(argv[2]);

    Particella *a = new Particella(m, c);
    Elettrone *e = new Elettrone();
    
    a->Print();
    e->Print();
    
    cout << "Proviamo a fare una particella b uguale ad a" << endl;
    Particella b(*a);
    b.Print();
    cout << "Proviamo a fare una particella b uguale all'elettrone e" << endl;
    Particella d(*e);
    d.Print();

    return 0;
}

    