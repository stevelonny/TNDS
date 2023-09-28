#include "calorimetro.hpp"
#include "../fmtlib.h"

int main(){

    EsperimentoCalorimetro cal;
    int n_volte{1000};
    cal.Analizza(1000);
    fmt::print("Media: {0} , Std: {1}\n", cal.getMean(), cal.getStd());
        
    return 0;
}