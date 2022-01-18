#include "solutore.hpp"
#include <vector>
#include <iomanip>

using namespace std;

int main(){
    x_Tanx fun;
    Bisezione sol;
    vector<double> valori;
    for(int i=0; i<20; i++){
        valori.push_back(sol.CercaZeriReference(i*M_PI, i*M_PI+M_PI_2, fun, 1e-6, 512));
        cout << "Passo " << i+1 << " : " << (valori[i]>10 ? setprecision(8) : setprecision(7)) << valori [i] << " ";
        cout << (sol.getFound() ? "Valore trovato " : "Valore non trovato ");
        cout << "Dopo " << sol.getNIterations() << " iterazioni su un massimo di " << sol.getNMaxIterations() << endl;
    }
    int c{0};
    for(int i=0; i<valori.size(); i++){
        isnan(valori[i]) ? c=c : c++;
    }
    cout << "Trovati " << c << " valori su " << 20 << endl;
    return 0;
}