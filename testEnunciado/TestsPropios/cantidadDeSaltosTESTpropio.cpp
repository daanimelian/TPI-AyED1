#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTESTpropio, todosSaltos){
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
    viaje v1 = {{1,p1},{2,p9}};
    viaje v2 = {{5,p7},{1,p1},{2,p2},{4,p3},{6,p5},{3,p7},{7,p5}};
    viaje v3 = {{1,p1}};
    viaje v4 = {{1,p1},{2,p1}};
    viaje v5 = {{1,p1},{2,p9},{3,p9}};
    EXPECT_EQ(cantidadDeSaltos(g,v1),1);
    EXPECT_EQ(cantidadDeSaltos(g,v2),4);
    EXPECT_EQ(cantidadDeSaltos(g,v3),0);
    EXPECT_EQ(cantidadDeSaltos(g,v4),0);
    EXPECT_EQ(cantidadDeSaltos(g,v5),1);
}