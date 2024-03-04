#include <iostream>
#include <fstream>
#include <vector>
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "TF1.h"
#include "../fmtlib.h"

#include "montecarlo.hpp"

using namespace std;

int main(int argc, const char** argv){
    if(argc!=2){
        fmt::print(stderr, "Sintassi errata! Uso del programma: {0} <precisione richiesta>\n", argv[0]);
        exit(-1);
    }
    //Apertura file
    vector<unsigned int> sample_size{100, 500, 1000, 5000, 10000, 50000, 100000};
    ifstream file_in;
    string title, savename;
    vector<double> sample;
    double min{1.5}, max{2.5};
    double temp;
    int c{0};
    vector<double> media;
    vector<double> hit;
    TCanvas can_media("media", "sample_media", 2000, 3000);
    can_media.Divide(2, 3);
    fmt::print("Valutiamo i dati ottenuti con il metodo della media...\n");
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("sample_{0}{1}.dat", "media_", sample_size[i]);
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
        TH1D hist_media(title.c_str(), title.c_str(), 100, min, max);
        can_media.cd(i+1);
        hist_media.SetTitle(title.c_str());
        //Riempiamo l'istogramma
        for(int j{0}; j<c; j++){
            hist_media.Fill(sample[j]);
        }
        fmt::print("La media del set di dati con N={1} è {0}\n", hist_media.GetMean(), sample_size[i]);
        fmt::print("L'errore della media {0}\n", hist_media.GetMeanError());
        fmt::print("La deviazione standard è {0}\n", hist_media.GetStdDev());
        media.push_back(hist_media.GetStdDev());
        hist_media.GetXaxis()->SetTitle("Valore integrale MC");
        hist_media.GetYaxis()->SetTitle("Frequenza");
        hist_media.DrawCopy();
        //Resettiamo tutto
        file_in.close();
        //can.Clear();
        sample.clear();
        c=0;
    }
    can_media.Print("hist_media.png");



    TCanvas can_hit("hit-or-miss", "sample_hit", 2000, 3000);
    can_hit.Divide(2, 3);
    fmt::print("Valutiamo i dati ottenuti con il metodo hit-or-miss...\n");
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("sample_{0}{1}.dat", "hit_", sample_size[i]);
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
        TH1D hist_hit(title.c_str(), title.c_str(), 50, min, max);
        can_hit.cd(i+1);
        hist_hit.SetTitle(title.c_str());
        //Riempiamo l'istogramma
        for(int j{0}; j<c; j++){
            hist_hit.Fill(sample[j]);
        }
        fmt::print("La media del set di dati con N={1} è {0}\n", hist_hit.GetMean(), sample_size[i]);
        fmt::print("L'errore della media {0}\n", hist_hit.GetMeanError());
        fmt::print("La deviazione standard è {0}\n", hist_hit.GetStdDev());
        hit.push_back(hist_hit.GetStdDev());
        hist_hit.GetXaxis()->SetTitle("Valore integrale MC");
        hist_hit.GetYaxis()->SetTitle("Numero campioni");
        hist_hit.DrawCopy();
        //Resettiamo tutto
        file_in.close();
        //can.Clear();
        sample.clear();
        c=0;
    }
    can_hit.Print("hist_hit.png");

    TCanvas can_error("error", "error", 1280, 780);
    TGraph  gmedia, ghit;
    TF1 * media_fit = new TF1("fit_media", "[0]/sqrt(x)", (double)sample_size.front()-10., (double)sample_size.back()+10.);
    TF1 * hit_fit = new TF1("fit_hit", "[0]/sqrt(x)", (double)sample_size.front()-10., (double)sample_size.back()+10.);

    for(int i{0}; i<sample_size.size(); i++){
        gmedia.SetPoint(i, sample_size[i], media[i]);
        ghit.SetPoint(i, sample_size[i], hit[i]);
    }

    double k_media, k_hit;

    can_error.cd();
    can_error.SetLogx();
    can_error.SetLogy();
    gmedia.SetTitle("Media");
    gmedia.GetXaxis()->SetTitle("N");
    gmedia.GetYaxis()->SetTitle("Errore");
    gmedia.SetMarkerColor(3);
    ghit.SetMarkerColor(4);
    ghit.SetTitle("Hit-or-Miss");
    gmedia.Fit(media_fit, "", "", sample_size.front()-10, sample_size.back()+10);
    k_media = media_fit->GetParameter(0);
    ghit.Fit(hit_fit, "", "", sample_size.front()-10, sample_size.back()+10);
    k_hit = hit_fit->GetParameter(0);
    gmedia.Draw("A*");
    ghit.Draw("*");
    can_error.SetTitle("Andamento Errore-N");
    can_error.BuildLegend();
    can_error.Print("errors.png");

    fmt::print("\nParametro k andamento erroe-N secondo la relazione errore=k/sqrt(N):\n");
    fmt::print("Metodo della media k_media = {0}\n", k_media);
    fmt::print("Metodo hit-or-miss k_hit = {0}\n", k_hit);
    fmt::print("Punti necessari per arrivare alla precisione richiesta ({0}):\n", argv[1]);
    double prec{atof(argv[1])};
    fmt::print("Metodo della media N_media = {0}\n", (int)pow((k_media/prec), 2));
    fmt::print("Metodo hit-or-miss N_hit = {0}\n", (int)pow((k_hit/prec), 2));

    return 0;
}