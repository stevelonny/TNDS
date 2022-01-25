#include "solutore.hpp"
#include "integratore.hpp"
#include "montecarlo.hpp"
#include "fmtlib.h"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TImage.h"
#include "TF1.h"
#include "FunzioneIntegrale.hpp"
#include <vector>

using namespace std;

double interp(double x1, double y1, double x2, double y2, double y);

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

int main(){
  
	// punto 1 :
    Bisezione bis;

    Fun f_funzione;

    double x_1{bis.CercaZeriReference(1, 2, f_funzione, 0.01, 100)};
    double x_1_inc{bis.getRPrec()};
    double x_2{bis.CercaZeriReference(3, 5, f_funzione, 0.01, 100)};
    double x_2_inc{bis.getRPrec()};
    double x_3{bis.CercaZeriReference(5, 6, f_funzione, 0.01, 100)};
    double x_3_inc{bis.getRPrec()};


    fmt::print("Punto 1 : gli zeri x1 = {0:>1.3f} +- {3:>1.3f}, x2 = {1:>1.3f} +- {4:>1.3f}, x3 = {2:>1.3f} +- {5:>1.3f} con precisione richiesta di {6:>1.2f}\n",
                x_1, x_2, x_3, x_1_inc, x_2_inc, x_3_inc, 0.01);
	// cout << "Punto 1 : gli zeri : x1 = " << x1zero << "   x2 = " << x2zero << "   x3 = " << x3zero << " [+/- " << prec_zeri << "]" << endl;

	// punto 2 e 3 :

    Trapezoidi trap;

    double int_x1_x2{trap.IntegrateSteps(x_1, x_2, 10, f_funzione)};
    double int1_inc{trap.getPrecision()};
    fmt::print("Punto 2 : Integrale = {0} +- {1}\n", int_x1_x2, int1_inc);

	// cout << "Punto 2 e 3 : Integrale = " << integrale << " +/- " << errore << endl;

	// punto 4 :

    double prec{0.64};
    vector<int> steps;
    vector<double> a_prec;
    //int n_step{10};
    int c{0};
    /*while(trap.getPrecision()>0.001){
        trap.IntegrateSteps(x_1, x_2, n_step, f_funzione);
        steps.push_back(trap.getIterations());
        a_prec.push_back(trap.getPrecision());
        fmt::print(" {0} | {1:1.4f} | {2}\n", steps[c], a_prec[c], n_step);
        c++;
        n_step
    } */
    
    while(trap.getPrecision()>0.001){
        trap.Integrate(x_1, x_2, prec, f_funzione);
        steps.push_back(trap.getIterations());
        a_prec.push_back(trap.getPrecision());
        //fmt::print(" {0} | {1:1.4f} | {2:1.4f}\n", steps[c], a_prec[c], prec);
        c++;
        prec /= 2.;
    }

    int nec_step{(int)(interp(steps.back(), a_prec.back(), steps[c-2], a_prec[c-2], 0.001))};

    fmt::print("Punto 4 : Numero di intervalli necessari per una precisione 0.001 = {0}\n", nec_step);

	// cout << "Punto 4 : Numero di intervalli necessari per una precisione " << errtilde << " = " << ntilde << endl;

	// punto 5 :

    MonteCarlo carlo(1);

    vector<unsigned int> sample_size{100, 500, 1000, 5000, 10000};
    vector<double> values(10000);
    vector<double> dev;
    vector<double> mean;
    string basetitle{"sample "};
    string title;
    double temp;
    TGraph  gmedia;

    TF1 * media_fit = new TF1("fit_media", "[0]/sqrt(x)", (double)sample_size.front()-10., (double)sample_size.back()+10.);
    MonteCarlo monte(1);
    fmt::print(stderr, "Calcolo i valori con metodo di montecarlo...\n");
    for(int i{0}; i<sample_size.size(); i++){
        title = fmt::format("{0}{1}{2}", basetitle, "media ", sample_size[i]);
        fmt::print(stderr, "({0}/{1})Calcolando {2}\n", i+1, sample_size.size(), title);
        for(int j{0}; j<10000; j++){    
            temp = monte.Media(f_funzione, x_1, x_2, sample_size[i]);
            values[j] = temp;
            cout << j+1 << "/10000\r";
            cout.flush();
        }
        mean.push_back(Mean(values));
        dev.push_back(StdDev(values));
        gmedia.SetPoint(i, sample_size[i], dev[i]);        
        //values.resize(sample_size[(i+1)<sample_size.size()?(i+1):i]);
        cout << endl;
    }

        gmedia.Fit(media_fit, "", "", 90, 10010);
        double k_media{media_fit->GetParameter(0)};

        fmt::print("\nPunto 5 : Parametro k andamento erroe-N secondo la relazione errore=k/sqrt(N): {0:2.2f} \n", k_media);
        fmt::print("Punto 5 : Numero punti necessari = {0}\n", (int)pow((k_media/0.001), 2));

	// cout << "Punto 5 : Punti richiesti (metodo media) per precisione " << errtilde << " = " << nrequired << endl;

	// punto 6 :

        int n_passi{(int)(fabs(x_3-x_1)/0.1+0.5)};
        TCanvas can("sium", "sium", 800, 600);
        TGraph g_passi;
        double h{0.1};
        double t{x_1};
        fmt::print("Punto 6, tabella dati\n");
        fmt::print(" x_1+t | F()\n");
        for(int i{0}; i<n_passi; i++){
            t += h;
            temp = trap.IntegrateSteps(x_1, t, 10, f_funzione);
            fmt::print(" {0:>3.2f} | {1:>5.3f} \n", t, temp);
            g_passi.SetPoint(i, t, temp);
        }

        can.cd();
        g_passi.SetTitle("Punto 6");
        g_passi.GetXaxis()->SetTitle("t");
        g_passi.GetYaxis()->SetTitle("y");
        g_passi.Draw("AL*");
        can.Print("punto6.png");

        FunzioneIntegrale funny(x_1);
        Bisezione bis_bis;
        double t_0{bis_bis.CercaZeriReference(4, 5, funny, 0.01, 1024)};
        fmt::print("Punto 7 : Zero della funzione integrale t0 = {0}\n", t_0);



	// grafico o for ( ) { cout << t << " " << ft << endl; }

	// punto 7 

	// cout <<  "Punto 7 : Zero della funzione integrale " << zero << "+/- " << prec_zeri << endl;

    return 0;
}


double interp(double x1, double y1, double x2, double y2, double y){
    //cerr << "valori " << x1 << " " << x2 << " " << y1 << " " << y2 << " " << y << endl; 
    return x1+((x1-x2)/(y1-y2))*(y-y1);
}