#include "puntomateriale.hpp"
#include <cassert>

#include "TApplication.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TPad.h"
#include "TCanvas.h"

const double d = 1e-10;

bool are_close(double, double);
void test_coordinates();
void test_coulomb_law();
void test_newton_law();

TGraph DoPlot(const PuntoMateriale &e, const PuntoMateriale &p, int low, int upper);

int main(int argc, char** argv){
    
    if(argc!=4){
        cerr << "Uso del programma: " << argv[0] << " x y z" << endl;
        exit(-1);
    }

    test_coordinates();
    test_coulomb_law();
    test_newton_law();

    double x = atof(argv[1]);
    double y = atof(argv[2]);
    double z = atof(argv[3]);

    Posizione pos(x, y, z);
    Elettrone el;
    Protone pr;
    
    PuntoMateriale ele(el, 0., 0., d/2);
    PuntoMateriale pro(pr, 0., 0., -d/2);
    
    CampoVettoriale E = ele.CampoElettrico(pos) + pro.CampoElettrico(pos);
    CampoVettoriale G = ele.CampoGravitazionale(pos) + pro.CampoGravitazionale(pos);

    cout << "Posizione ( " << pos.getX() << " , " << pos.getY() << " , " << pos.getZ() << " )";
    cout << " distanza dall'origine " << pos.getDistance() << endl;
    cout << "Campo elettrico E = ( " << E.getFx() << " , " << E.getFy() << " , " << E.getFz() << " )" << endl;
    cout << "di modulo |E| = " << E.Modulo() << endl;
    cout << "Campo gravitazionale G = ( " << G.getFx() << " , " << G.getFy() << " , " << G.getFz() << " )" << endl;
    cout << "di modulo |G| = " << G.Modulo() << endl;

    TApplication app("app", 0, 0);
    TGraph campo = DoPlot(ele, pro, 100, 1000);
    TCanvas c1;
    c1.SetLogy();
    c1.SetLogx();
    campo.SetTitle("Andamento distanza-E logaritmico");
    campo.GetXaxis()->SetTitle("Distanza [m]");
    campo.GetYaxis()->SetTitle("Campo E [N/C]");
    campo.GetXaxis()->SetRangeUser(100*d, 1000*d);
    campo.Draw("APC");

    app.Run();

    return 0;
}

TGraph DoPlot(const PuntoMateriale &e, const PuntoMateriale &p, int low, int upper){
  TGraph campo;
  double distance;
  for(int i=low; i<upper; i++){
    distance = d*(double)i;
    campo.SetPoint(i, distance, (e.CampoElettrico(distance, 0, 0)+p.CampoElettrico(distance, 0, 0)).Modulo());
  }
  return campo;
}

bool are_close(double calculated, double expected) {
  double epsilon = 1e-7;
  return fabs(calculated - expected) < epsilon;
}

void test_coordinates(){
  Posizione p{1, 2, 3};
  
  assert(are_close(p.getX(), 1.0));
  assert(are_close(p.getY(), 2.0));
  assert(are_close(p.getZ(), 3.0));

  assert(are_close(p.getR(), 3.7416573867739));
  assert(are_close(p.getPhi(), 1.1071487177941));
  assert(are_close(p.getTheta(), 0.64052231267943));

  assert(are_close(p.getRho(), 2.2360679774998));
}

void test_coulomb_law(){
  // 0.5 µC charge with no mass (irrelevant for the electric field)
  PuntoMateriale particella{1.0, 5e-7, 5, 3, -2, };
  Posizione p{-2, 4, 1};
  
  CampoVettoriale V{particella.CampoElettrico(p)};
  
  assert(are_close(V.getFx(), -69.41150052142065));
  assert(are_close(V.getFy(), 9.915928645917235));
  assert(are_close(V.getFz(), 29.747785937751708));
}

void test_newton_law(){
  // 10⁹ tonnes, without charge (irrelevant for the gravitational field)
  PuntoMateriale particella{1e12, 0, 5, 3, -2, };
  Posizione p{-2, 4, 1};
  
  CampoVettoriale V{particella.CampoGravitazionale(p)};
  assert(are_close(V.getFx(), -1.0302576701177));
  assert(are_close(V.getFy(), 0.14717966715968));
  assert(are_close(V.getFz(), 0.44153900147903));
}