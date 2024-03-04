#include "montecarlo.hpp"
#include "../fmtlib.h"

using namespace std;

#include <vector>
#include <fstream>

int main(){
    vector<unsigned int> sample_size{100, 500, 1000, 5000, 10000, 50000, 100000};
    string basetitle{"sample_"};
    string title;
    ofstream file_out;
    double temp;
    MonteCarlo monte(1);
    Seno sen;
    fmt::print(stderr, "Calcoliamo prima i valori con il metodo media. Output: <sample_media_N.dat>\n");
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("{0}{1}{2}.dat", basetitle, "media_", sample_size[i]);
        fmt::print(stderr, "({0}/{1})Calcolando {2}\n", i+1, sample_size.size(), title);
        file_out.open(title);
        for(int j{0}; j<10000; j++){    
            temp = monte.Media(sen, 0., M_PI, sample_size[i]);
            file_out << temp << endl;
            cout << j+1 << "/10000\r";
            cout.flush();
        }
        cout << endl;
        file_out.close();
    }
    fmt::print(stderr, "Calcoliamo infine i valori con il metodo hit-or-miss. Output: <sample_hit_N.dat>\n");
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("{0}{1}{2}.dat", basetitle, "hit_", sample_size[i]);
        fmt::print(stderr, "({0}/{1})Calcolando {2}\n", i+1, sample_size.size(), title);
        file_out.open(title);
        for(int j{0}; j<10000; j++){    
            temp = monte.Hit(sen, 0., M_PI, sample_size[i], 1.);
            file_out << temp << endl;
            cout << j+1 << "/10000\r";
            cout.flush();
        }
        cout << endl;
        file_out.close();
    }
    fmt::print(stderr, "Terminato!\n");
}
