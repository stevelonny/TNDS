#include "solutore.hpp"
#include <iomanip>

using namespace std;

int main(int argc, const char** argv){
    if(argc!=8){
        cerr << "Troppi pochi argomenti!" << endl;
        cerr << "Uso: " << argv[0] << "[parametri parabola] <a> <b> <c> [parametri ricerca] <min> <max> <prec> <nmaxiterazioni>" << endl;
        exit(-1);
    }
    Parabola para(atof(argv[1]), atof(argv[2]), atof(argv[3]));
    Bisezione sol;
    cout << '\t' << "Metodo della bisezione" << endl;
    double zero = sol.CercaZeriReference(atof(argv[4]), atof(argv[5]), para, atof(argv[6]), (atoi(argv[7])>0 ? atoi(argv[7]) : 100));
    cout << (sol.getFound() ? "Valore trovato" : "Valore non trovato") << endl;
    cout << "Dopo " << sol.getNIterations() << " iterazioni su un massimo di " << sol.getNMaxIterations();
    cout << " cercando il valore con una precisione di " << sol.getPrecisione() << endl;
    cout << (isnan(zero) ? "Ipotesi non rispettate " : "Valore trovato : ") << setprecision(1+(int)fabs(log10(atof(argv[6])))) << zero << endl;
    Secante sec;
    cout << '\t' << "Metodo della secante" << endl;
    zero = sec.CercaZeriReference(atof(argv[4]), atof(argv[5]), para, atof(argv[6]), (atoi(argv[7])>0 ? atoi(argv[7]) : 100));
    cout << (sec.getFound() ? "Valore trovato" : "Valore non trovato") << endl;
    cout << "Dopo " << sec.getNIterations() << " iterazioni su un massimo di " << sec.getNMaxIterations();
    cout << " cercando il valore con una precisione di " << sec.getPrecisione() << endl;
    cout << (isnan(zero) ? "Ipotesi non rispettate " : "Valore trovato : ") << setprecision(1+(int)fabs(log10(atof(argv[6])))) << zero << endl;
    
    return 0;
}