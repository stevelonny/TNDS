#include <fstream>
#include <vector>
#include "../fmtlib.h"

#include "funzioni.hpp"
#include "integratore.hpp"
#include "montecarlo.hpp"


using namespace std;

//Media
template <typename T> double Mean(const vector<T> & vett){ //teniamo double che è meglio
    T mean;
    T sum = 0;
    
    for(int i=0; i<vett.size(); i++){
        sum+=vett[i];
    }
    mean = sum/(double)vett.size();

    return mean;
}
//Deviazione standard
template <typename T> double StdDev(const vector<T> &data){
    double dev;
    double sum=0;
    double mean=Mean(data);

    for(int i=0; i<data.size(); i++){
        sum+=pow((data[i]-mean), 2);
    }
    dev = sqrt(sum/(double)data.size());

    return dev;
}

vector<double> power_law(double x1, double x2, double y1, double y2);
double evaluate(double h, double m, double k);

int main(){

    Fun_1 fun1;

    Midpoint point;
    Midright right;

    double real1{(3./16.)*M_E*M_E};

    int n_points{2};
    double temp, temp_r;
    vector<double> error, error_r;
    vector<double> h, h_r;
    vector<double> valori;
    vector<double> right_valori;

    for(int i{0}; i<10; i++){
        n_points = (2 << i);
        temp = point.Integrate(0, sqrt(M_E), n_points, fun1);
        temp_r = right.Integrate(0, sqrt(M_E), n_points, fun1);
        error.push_back(fabs(real1-temp));
        error_r.push_back(fabs(real1-temp_r));
        h_r.push_back(right.getH());
        h.push_back(point.getH());
        valori.push_back(temp);
        right_valori.push_back(temp_r);
        //fmt::print("{0:>5} | {1:>1.8f} | {2:>1.8f} | {3:>1.4f}\n", n_points, temp, fabs(real1-temp), point.getH());
    }
    vector<double> param{power_law(h[0], h[9], error[0], error[9])};
    vector<double> param_r{power_law(h_r[0], h_r[9], error_r[0], error_r[9])};
    FILE * file_out = fopen("soluzione.txt", "w+b");
    //fmt::print("{0} {1} {2} {3}\n", h[0], h[9], error[0], error[9]);
    fmt::print("Relazione di potenza per midpoint: k1 = {0:<1.2f} , k2 = {1:<1.2f} \n", exp(param[1]), param[0]);
    fmt::print(file_out, "Relazione di potenza per midpoint: k1 = {0:<1.2f} , k2 = {1:<1.2f} \n", exp(param[1]), param[0]);
    fmt::print("Relazione di potenza per midright: k1 = {0:<1.2f} , k2 = {1:<1.2f} \n", exp(param_r[1]), param_r[0]);
    fmt::print(file_out, "Relazione di potenza per midright: k1 = {0:<1.2f} , k2 = {1:<1.2f} \n", exp(param_r[1]), param_r[0]);
    int n{2};
    fmt::print("{0} | {1:>10} | {2:>10} | {3:>6} | {4:>10} | {5:>10} | {2:>10} | {3:>6} | {4:>10}\n",
            "Punti", "Midpoint", "Delta", "h", "Err stima" , "Midright");
    fmt::print(file_out, "{0} | {1:>10} | {2:>10} | {3:>6} | {4:>10} | {5:>10} | {2:>10} | {3:>6} | {4:>10}\n",
            "Punti", "Midpoint", "Delta", "h", "Err stima" , "Midright");
    for(int i{0}; i<10; i++){
        n = (2 << i);
        fmt::print("{0:>5} | {1:>1.8f} | {2:>1.8f} | {3:>1.4f} | {4:>1.8f} | {5:>1.8f} | {6:>1.8f} | {7:>1.4f} | {8:>1.8f} \n",
            n, valori[i], error[i], h[i], evaluate(h[i], param[0], param[1]), right_valori[i], error_r[i], h_r[i], evaluate(h_r[i], param_r[0], param_r[1]));
        fmt::print(file_out, "{0:>5} | {1:>1.8f} | {2:>1.8f} | {3:>1.4f} | {4:>1.8f} | {5:>1.8f} | {6:>1.8f} | {7:>1.4f} | {8:>1.8f} \n",
            n, valori[i], error[i], h[i], evaluate(h[i], param[0], param[1]), right_valori[i], error_r[i], h_r[i], evaluate(h_r[i], param_r[0], param_r[1]));

    }

    MonteCarlo carlo(1);
    vector<double> carlo_valori;
    for(int i{0}; i<1000; i++){
        carlo_valori.push_back(carlo.Media(fun1, 0, sqrt(M_E), 16));
    }
    double mean{Mean(carlo_valori)};
    double dev{StdDev(carlo_valori)/sqrt(carlo_valori.size())};
    fmt::print("Valore ottenuto con il metodo della media: {0:1.2f} +- {1:1.2f}\n", mean, dev);
    fmt::print(file_out, "Valore ottenuto con il metodo della media: {0:1.2f} +- {1:1.2f}\n", mean, dev);
    fmt::print("Numero di punti per ottenre la stessa precisione con midpoint: {0}\n", (int)(sqrt(M_E)/pow(dev/exp(param[1]), 1./param[0])));
    fmt::print(file_out, "Numero di punti per ottenre la stessa precisione con midpoint: {0}\n", (int)(sqrt(M_E)/pow(dev/exp(param[1]), 1./param[0])));
    
    Fun_2 fun2;
    fmt::print("Usiamo midpoint, poichè in x = 2 c'è un asintoto verticale, che coinciderebbe con l'estremo destro usato da midright\n");
    fmt::print(file_out, "Usiamo midpoint, poichè in x = 2 c'è un asintoto verticale, che coinciderebbe con l'estremo destro usato da midright\n");
    
    double valore2{point.Integrate(0, 2, 1024, fun2)};
    fmt::print("Valore ottenuto con {0} punti: {1:1.2f}\n", 1024, valore2);
    fmt::print(file_out, "Valore ottenuto con {0} punti: {1:1.2f}\n", 1024, valore2);
    return 0;
}

vector<double> power_law(double x1, double x2, double y1, double y2){
    double deltax = log(x1)- log(x2);
    double deltay = log(y1) - log(y2);
    double q = (log(y2)*log(x1) - log(y1)*log(x2))/deltax;
    double m = (deltay)/(deltax);
    return {m, q};
}

double evaluate(double h, double m, double q){
    return exp(q)*pow(h, m);
}

