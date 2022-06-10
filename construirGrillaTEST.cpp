#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(construirGrillaTEST, nombresCorrectosDistanciaParNParMImparArg){

    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);

    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                  make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                  make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                  make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                  make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                  make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
                  };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_EQ(n*m, g.size());
}
TEST(construirGrillaTESTpropio,nombresIncorrectosNParMImpar){  // Los nombres son incorrectos porque g es igual a gres invertida
    int n = 2;
    int m = 3;

    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);


    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.7), make_tuple(1,1)),
                   make_tuple(puntoGps(-33.0,-57.7), puntoGps(-33.45,-57.4), make_tuple(1,2)),
                   make_tuple(puntoGps(-33.0,-57.4), puntoGps(-33.45,-57.1), make_tuple(1,3)),
                   make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.7), make_tuple(2,1)),
                   make_tuple(puntoGps(-33.45,-57.7), puntoGps(-33.9,-57.4), make_tuple(2,2)),
                   make_tuple(puntoGps(-33.45,-57.4), puntoGps(-33.9,-57.1), make_tuple(2,3))
    };

    grilla g = construirGrilla(esq2,esq1,n,m);
    int i = 0;
    EXPECT_EQ(get<0>(g[i]), get<1>(gres[gres.size()  - i - 1]));
    EXPECT_EQ(get<1>(g[i]), get<0>(gres[gres.size()  - i - 1]));

}

TEST(construirGrillaTESTpropio, nombresIncorrectosNParMPar){
    int n = 2;
    int m = 4;


    gps esq1 = puntoGps(-33.0,-58.0);
    gps esq2 = puntoGps(-33.9,-57.1);


    grilla gres = {make_tuple(puntoGps(-33.0,-58.0), puntoGps(-33.45,-57.775), make_tuple(1,1)),
                   make_tuple(puntoGps(-33.0,-57.775), puntoGps(-33.45,-57.55), make_tuple(1,2)),
                   make_tuple(puntoGps(-33.0,-57.55), puntoGps(-33.45,-57.325), make_tuple(1,3)),
                   make_tuple(puntoGps(-33.0,-57.325), puntoGps(-33.45,-57.1), make_tuple(1,4)),
                   make_tuple(puntoGps(-33.45,-58.0), puntoGps(-33.9,-57.775), make_tuple(2,1)),
                   make_tuple(puntoGps(-33.45,-57.775), puntoGps(-33.9,-57.55), make_tuple(2,2)),
                   make_tuple(puntoGps(-33.45,-57.55), puntoGps(-33.9,-57.325), make_tuple(2,3)),
                   make_tuple(puntoGps(-33.45,-57.325), puntoGps(-33.9,-57.1), make_tuple(2,4))
    };

    grilla g = construirGrilla(esq2,esq1,n,m);
    int i = g.size() -1;
    EXPECT_EQ(get<0>(g[i]), get<1>(gres[gres.size()  - i - 1]));
    EXPECT_EQ(get<1>(g[i]), get<0>(gres[gres.size()  - i - 1]));

}