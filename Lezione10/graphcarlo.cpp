#include "montecarlo.cpp"
#include "../fmtlib.h"

#include <vector>
#include <fstream>

int main(){
    vector<unsigned int> sample_size{100, 500, 1000, 5000, 10000};
    string basetitle{"sample_"};
    string title;
    ofstream file_out;
    double temp;
    MonteCarlo monte(1);
    Seno sen;
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("{0}{1}.txt", basetitle, sample_size[i]);
        file_out.open(title);
        for(int j{0}; j<sample_size[i]; j++){    
            temp = monte.Media(sen, 0., M_PI, 10000);
            file_out << temp << endl;
        }
        file_out.close();
    }
}
