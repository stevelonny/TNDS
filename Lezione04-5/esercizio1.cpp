#include "posizione.hpp"
#include <cassert>

bool are_close(double, double, double);
void test_coordinates();

int main(int argc, char** argv){
    if(argc!=4){
        cerr << "Uso del programma: " << argv[0] << " x y z" << endl;
        exit(-1);
    }

    double x = atof(argv[1]);
    double y = atof(argv[2]);
    double z = atof(argv[3]);

    Posizione P(x, y, z);

    cout << "Coordinate cartesiane: " <<  P.getX() << " " << P.getY() << " " << P.getZ() << endl;
    cout << "Coordinate sferiche: " <<  P.getR() << " " << P.getPhi() << " " << P.getTheta() << endl;
    cout << "Coordinate cilindriche: " <<  P.getRho() << " " << P.getPhi() << " " << P.getZ() << endl;

    return 0;
}

bool are_close(double calculated, double expected, double epsilon = 1e-7) {
  return fabs(calculated - expected) < epsilon;
}

void test_coordinates(){
  Posizione p{1, 2, 3};
  
  assert(are_close(p.getX(), 1.0));
  assert(are_close(p.getY(), 2.0));
  assert(are_close(p.getZ(), 3.0));
  
  assert(are_close(p.getR(), 3.7416573867739));
  assert(are_close(p.getPhi(), 0.64052231267943));
  assert(are_close(p.getTheta(), 1.1071487177941));

  assert(are_close(p.getRho(), 2.2360679774998));
}