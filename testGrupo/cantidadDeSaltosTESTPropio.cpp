#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(cantidadDeSaltosTEST, sinSaltos){
grilla g = construirGrilla(puntoGps(180.0,0.0),puntoGps(0.0,90), 1, 2);

gps p1 = puntoGps(0, 0);
gps p2 = puntoGps(180, 90);

viaje v = {medicion(1.5, p1),
           medicion(1.6, p2)};

EXPECT_EQ(cantidadDeSaltos(g,v),0);
}
