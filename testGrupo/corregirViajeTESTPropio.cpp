#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(corregirViajeTEST, faltaElPrimeroYUnIntermedio){
    viaje v = {medicion(0, puntoGps(0.0, 0.0)),
               medicion(10, puntoGps(10.1, 20.1)),
               medicion(20, puntoGps(10.2, 20.2)),
               medicion(30, puntoGps(10.3, 20.3)),
               medicion(40, puntoGps(0.0, 0.0)),
               medicion(50, puntoGps(10.5, 20.5))};

    viaje res = {medicion(0, puntoGps(10.0, 20.0)),
                 medicion(10, puntoGps(10.1, 20.1)),
                 medicion(20, puntoGps(10.2, 20.2)),
                 medicion(30, puntoGps(10.3, 20.3)),
                 medicion(40, puntoGps(10.4, 20.4)),
                 medicion(50, puntoGps(10.5, 20.5))};
    vector<tiempo> errores = {0, 40};

    corregirViaje(v, errores);
    EXPECT_EQ(v.size(),res.size());

    for (int i = 0; i < res.size(); ++i) {
        EXPECT_NEAR(obtenerLatitud(obtenerPosicion(v[i])),
                    obtenerLatitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_NEAR(obtenerLongitud(obtenerPosicion(v[i])),
                    obtenerLongitud(obtenerPosicion(res[i])), 0.00001);
        EXPECT_EQ(obtenerTiempo(v[i]),obtenerTiempo(res[i]));
    }
}


