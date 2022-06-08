#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(buscoCeldaDeUnViajeTEST, celdas){
gps p1 = {85,10};
gps p2 = {85,50};
gps p3 = {85,85};
gps p4 = {50,10};
gps p5 = {50,50};
gps p6 = {50,85};
gps p7 = {10,10};
gps p8 = {10,50};
gps p9 = {10,85};
grilla g = construirGrilla({90,0},{0,90},3,3);
viaje v = {{4,p4},{1,p1},{3,p3},{2,p2},{18,p6},{9,p5}};
EXPECT_EQ(buscoCeldaDeUnViaje(v[0],g),g[3]);
EXPECT_EQ(buscoCeldaDeUnViaje(buscoSiguientePunto(v,v[1]),g),g[1]);
}