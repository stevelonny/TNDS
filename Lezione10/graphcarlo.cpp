#include <iostream>
#include <fstream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "../fmtlib.h"

#include "montecarlo.hpp"

using namespace std;

int main(int argc, const char** argv){
    //Apertura file
    vector<unsigned int> sample_size{100, 500, 1000, 5000, 10000};
    ifstream file_in;
    ofstream file_out;
    file_out.open("errors.dat");
    string title, savename;
    vector<double> sample;
    double min{1.5}, max{2.5};
    double temp;
    int c{0};
    TCanvas can("can", "samplecan");
    TH1F sample_hist("sample", "sample", 100, min, max);
    sample_hist.StatOverflows(kTRUE);
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("sample_{0}.txt", sample_size[i]);
        //Lettura dati da file a vettore
        fmt::print(stderr, "({0}/{1})Lettura file {2}\n", i+1, sample_size.size(), title);
        file_in.open(title);
        if(file_in.fail()){
            fmt::print(stderr, "Errore nella lettura del file. Chiusura\n");
            exit(-2);
        }
        while(file_in >> temp){
            sample.push_back(temp);
            c++;
        }
        fmt::print(stderr, "({0}/{1})Terminato. Valori letti: {2}\n", i+1, sample_size.size(), c);
        //Ricerca min e max per istogramma
        min = *min_element(sample.begin(), sample.end());
        max = *max_element(sample.begin(), sample.end());
        can.cd();
        sample_hist.SetTitle(title.c_str());
        sample_hist.SetMinimum(min);
        sample_hist.SetMaximum(max);
        //Riempiamo l'istogramma
        for(int j{0}; j<c; j++){
            sample_hist.Fill(sample[i]);
        }
        fmt::print("La media del set di dati con N={1} è {0}\n", sample_hist.GetMean(), sample_size[i]);
        fmt::print("L'errore della media {0}\n", sample_hist.GetMeanError());
        fmt::print("La deviazione standard è {0}\n", sample_hist.GetStdDev());
        file_out << sample_hist.GetStdDev() << endl;        
        sample_hist.GetXaxis()->SetTitle("Valore integrale MC");
        sample_hist.GetYaxis()->SetTitle("Frequenza");
        sample_hist.Draw();
        savename = fmt::format("sample_{0}.png", argv[1]);
        can.Print(savename.c_str());
        //Resettiamo tutto
        file_in.close();
        can.Clear();
        sample_hist.Reset();
        sample_hist.ResetStats();
        sample.clear();
        c=0;
    }
    file_out.close();
    
    return 0;
}