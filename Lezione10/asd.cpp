#include <iostream>
#include <vector>
#include "random.hpp"
#include "TApplication.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TAxis.h"

using namespace std;

int main(){
    TApplication app("app", 0, 0);
    cout << sizeof(unsigned int) << endl;
    RandomGen sium(1);

    int nmax = 1;
    TH1F unif("Uniforme", "Uniforme", 100, 0, 10);
    //TH1F asd("Uniforme", "Uniforme", 100, 0, 10);
    for(int k{0}; k<nmax; k++){
        //asd.Fill(sium.Gauss(5,1));
        unif.Fill(sium.GaussAR(5,1));
    }

    TCanvas can2("Uniforme", "Uniforme");
    can2.cd();
    unif.GetXaxis()->SetTitle("x [U.A.]");
    unif.GetYaxis()->SetTitle("N");
    unif.Draw();

    app.Run();

    return 0;
}