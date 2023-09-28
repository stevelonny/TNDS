#include "integratore.hpp"
#include "../fmtlib.h"

using namespace std;

int main(){

    Sium fun;

    Trapezoidi int_prec;

    double real_val{sqrt(2.*M_PI)};

    double prec{1e-6};

    double value{int_prec.Integrate(-5., 5., prec, fun)};
    double r_prec{int_prec.getPrecision()};
    int n_iterations{int_prec.getIterations()};

    fmt::print("Valore trovato con il metodo dei trapezioidi: {0} , con una precisione di {1} , dopo {2} iterazioni.\n", value, r_prec, n_iterations);
    fmt::print("Delta da valore con estremi all'infinito: {0}\n", fabs(real_val-value));





    return 0;
}