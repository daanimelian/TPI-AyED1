#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

vector<viaje> g = {{
                   medicion(1.5,puntoGps(2.5, 2.89996)),
                   medicion(1.7,puntoGps(2.5, 2.89997)),
                   medicion(1.9,puntoGps(2.5, 2.89998))},
                   {
                    medicion(2.5,puntoGps(2.5, 2.89996)),
                    medicion(2.6,puntoGps(2.5, 2.89997)),
                    medicion(2.7,puntoGps(2.5, 2.89998))},
                   {
                    medicion(0.5,puntoGps(2.5, 2.89996)),
                    medicion(0.6,puntoGps(2.5, 2.89997)),
                    medicion(0.7,puntoGps(2.5, 2.89998))},
                   };


TEST(flotaTotalTEST, todosDespuesDeFranja){
    EXPECT_EQ(flota(g, 0.0, 0.4), 0);
}

TEST(flotaTotalTEST, unoEnFranja){
    EXPECT_EQ(flota(g, 2.0, 2.5), 1);
}

TEST(flotaTotalTEST, igualAFranja){
    EXPECT_EQ(flota(g, 1.5, 1.9), 1);
    EXPECT_EQ(flota(g, 1.5, 2.0), 1);
    EXPECT_EQ(flota(g, 2.0, 2.7), 1);
}
