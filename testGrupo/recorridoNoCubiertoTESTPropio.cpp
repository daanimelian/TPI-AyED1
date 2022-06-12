#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}

using namespace std;

const gps P = puntoGps(-31.465027, -64.212973);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
                      };

const recorrido RRulos = {P,
                         desviarPunto(P, 1000, 0),
                         desviarPunto(P, 2000, 0),
                         desviarPunto(P, 3000, 0),
                         desviarPunto(P, 4000, 0),
                         desviarPunto(P, 5000, 0),
                         desviarPunto(P, 5000, 100),
                         desviarPunto(P, 4000, 100),
                         desviarPunto(P, 3000, 100),
                         desviarPunto(P, 2000, 100),
                         desviarPunto(P, 1000, 100),
                         desviarPunto(P, 0, 0)
};


TEST(recorridoNoCubiertoTEST, viajeConImperfeccionIgualAlUmbral){
    viaje v = {};
    const recorrido R_2 = {P};


    for(int i = 0; i < R_2.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, 2000)));
    }

    vector<gps> res = recorridoNoCubierto(v, R_2, distEnKM(obtenerPosicion(v[0]), R_2[0]));
    EXPECT_EQ(res.size(), 1);
    ASSERT_ELEMENTS(res, {R_2[0]});

}


