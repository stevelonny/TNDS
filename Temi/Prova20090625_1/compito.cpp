#include "resistenza.hpp"

using namespace std;

int main(){

    PonteAFilo ponte;
    TGraph errore;
    vector<vector<double>> resistenze{{200, 500, 900, 1500, 3000},{}};
    for(int i{0}; i<resistenze[0].size(); i++){
        resistenze[1].push_back(ponte.Analizza(resistenze[0][i]));
        errore.SetPoint(i, resistenze[0][i], resistenze[1][i]);
    }
    errore.SetTitle("Errore");
    errore.GetXaxis()->SetTitle("R [ohm]");
    errore.GetYaxis()->SetTitle("Errore %");
    TCanvas can("can", "can", 800, 600);
    can.cd();
    errore.Draw("ALP*");
    can.Print("errore.png");
    auto min = min_element(resistenze[1].begin(), resistenze[1].end());
    int index = distance(resistenze[1].begin(), min);
    double min_r = resistenze[0][index];
    fmt::print("Valore migliore di R = {0:>4.0f} , con errore associato {1:>1.2f}\n", min_r, *min);
    FILE * fileout = fopen(FILENAME, "a+");
    fmt::print(fileout, "Valore migliore di R = {0:>4.0f} , con errore associato {1:>1.2f}\n", min_r, *min);

    return 0;
}