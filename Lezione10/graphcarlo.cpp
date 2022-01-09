#include <iostream>
#include <fstream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
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
    file_out.open("errors.txt");
    string title, savename;
    vector<double> sample;
    double min{1.5}, max{2.5};
    double temp;
    int c{0};
    TCanvas can("can", "samplecan");
    TH1D * sample_hist;
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
        sample_hist = new TH1D(title.c_str(), title.c_str(), 100, min, max);
        can.cd();
        sample_hist->SetTitle(title.c_str());
        //Riempiamo l'istogramma
        for(int j{0}; j<c; j++){
            sample_hist->Fill(sample[j]);
        }
        fmt::print("La media del set di dati con N={1} è {0}\n", sample_hist->GetMean(), sample_size[i]);
        fmt::print("L'errore della media {0}\n", sample_hist->GetMeanError());
        fmt::print("La deviazione standard è {0}\n", sample_hist->GetStdDev());
        file_out << sample_size[i] << '\t' << sample_hist->GetStdDev() << endl;        
        sample_hist->GetXaxis()->SetTitle("Valore integrale MC");
        sample_hist->GetYaxis()->SetTitle("Frequenza");
        sample_hist->Draw();
        savename = fmt::format("sample_{0}.png", sample_size[i]);
        can.Print(savename.c_str());
        //Resettiamo tutto
        file_in.close();
        can.Clear();
        delete sample_hist;
        sample.clear();
        c=0;
    }
    file_out.close();

    return 0;
}