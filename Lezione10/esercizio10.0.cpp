#include <iostream>
#include <vector>
#include "random.hpp"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TAxis.h"

using namespace std;

int main(){
    //TApplication app("app", 0, 0);
    //cout << sizeof(unsigned int) << endl;
    RandomGen r_unif(1);
    RandomGen r_expo(1);
    RandomGen r_gar(1);
    RandomGen r_gbox(1);

    int nmax = 10000;
    TH1F unif("Uniforme", "Uniforme", 100, 5, 10);
    TH1F expo("Esponenziale", "Esponenziale", 100, 0, 10);
    TH1F gaussar("Gauss AR", "Gauss AR", 100, -3, 5);
    TH1F gaussbox("Gauss Box-Muller", "Gauss Box-Muller", 100, -3, 5);

    for(int k{0}; k<nmax; k++){
        unif.Fill(r_unif.Unif(5, 10));
        expo.Fill(r_expo.Exp(1));
        gaussar.Fill(r_gar.GaussAR(1, 1));
        gaussbox.Fill(r_gbox.Gauss(1, 1));
    }

    TCanvas can("Uniforme", "Uniforme", 1200, 1200);
    can.DivideSquare(4);
    can.cd(1);
    unif.GetXaxis()->SetTitle("x [U.A.]");
    unif.GetYaxis()->SetTitle("N");
    unif.Draw();
    can.cd(2);
    expo.GetXaxis()->SetTitle("x [U.A.]");
    expo.GetYaxis()->SetTitle("N");
    expo.Draw();
    can.cd(3);
    gaussar.GetXaxis()->SetTitle("x [U.A.]");
    gaussar.GetYaxis()->SetTitle("N");
    gaussar.Draw();
    can.cd(4);
    gaussbox.GetXaxis()->SetTitle("x [U.A.]");
    gaussbox.GetYaxis()->SetTitle("N");
    gaussbox.Draw();
    can.Print("distribuzioni.png");
    //app.Run();

    return 0;
}