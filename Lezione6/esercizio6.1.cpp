#include "funzioni.hpp"

using namespace std;

int main(const int argc, const char** argv){

    if(argc!=4){
        cerr << "Uso del programma: " << argv[0] << " <a> <b> <c>" << endl;
        exit(-1);
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double c = atof(argv[3]);

    Parabola para(a, b, c);
    double xv = -(para.getB()/(2*para.getA()));

    cout << "Valore della parabola di parametri a,b,c: " << a << " " << b << " " << c << " nell'ascissa del vertice xv=" << xv << endl;
    cout << "f(xv) = " << para.Eval(xv) << endl;

    return 0;
}