#include "stats.h"

int main(int argc, const char *argv[]) {

    if (argc<3){
        cout << "Uso del programma: " << argv[0] << " ndata filename" << endl;
        return -1;
    }
    
    int ndata = atoi(argv[1]);
    
    const char* filename = argv[2];

    Vettore data = Read(filename, ndata);

    cout << endl << data[0] << " " << data[1] << endl;
    cout << endl << data.GetComponent(0) << " " << data.GetComponent(1) << endl << endl;

    Print(data, 10);
    cout << endl << data.GetN() << endl;

    cout << "Media: " << Mean(data) << endl;
    cout << "Deviazione standard: " << StdDev(data) << endl;
    cout << "Varianza: " << Variance(data) << endl << endl;

    Print(data, 10);
    cout << endl << data.GetN() << endl;

    cout << "Mediana: " << Median(data) << endl << endl;

    Print(data, 10);
    cout << endl << data.GetN() << endl;
    cout << "proviamo a riordinare agento per operator" << endl;

    Sort(data);

    Print(data, 10);
    cout << endl << data.GetN() << endl;

    Write("out.txt", data, data.GetN());

    return 0;
}