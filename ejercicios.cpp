#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t = maxTiempo(v) - minTiempo(v);

    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d = 0;
    int i = 0;
    while (i < v.size()){
        d = d + (distEnKM(obtenerPosicion(v[i]), obtenerPosicion(buscoSiguientePunto(v, v[i]))));
        i = i +1;
    }

    return d;
}

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/
bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    int i = 0;
    while (i < v.size()){
        if (velocidad(v[i], buscoSiguientePunto(v, v[i])) > 80) {
            resp = true;
            i = v.size();
        }
        i = i +1;
    }
    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp;
    int i = 0; int k = 0; bool estaDentro = false;
    while (k < r.size()){
        while (i < v.size()){
            if (distEnKM(obtenerPosicion(v[i]), r[k]) < (u/1000)) {
                estaDentro = true;
                i = v.size();
            }
            i = i + 1;
        }
        if (!estaDentro)
            resp.push_back(r[k]);
        i = 0;
        k = k + 1;
        estaDentro = false;
    }

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp;
    int i = 0;
    while (i < f.size()){
        if ((minTiempo(f[i]) > t0 && maxTiempo(f[i]) < tf)
            || (minTiempo(f[i]) < t0 && maxTiempo(f[i]) > t0 )
            || (minTiempo(f[i]) < tf && maxTiempo(f[i]) > tf)
            || (minTiempo(f[i]) < t0 && maxTiempo(f[i]) > tf)) // achicar esto
            resp = resp + 1;
        i = i + 1 ;
    }

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/
grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {}; int k = 1; int j = 1;
    celda c; gps a; gps b;
    double maxlatitud = obtenerLatitud(esq1);
    double minlatitud = obtenerLatitud(esq2);
    double maxlongitud = obtenerLongitud(esq2);
    double minlongitud = obtenerLongitud(esq1);
    while(k < n+1){
        while (j < m+1) {
            a = {(maxlatitud - ((k - 1) * ((maxlatitud - minlatitud) / n))),
                 (minlongitud + ((j - 1)* ((maxlongitud - maxlongitud) / m)))};
            b = {(maxlatitud - k * ((maxlatitud - minlatitud) / n)),
                 (minlongitud + (j * ((maxlongitud - maxlongitud) / m)))};
            c = {a, b, {k, j}};
            resp.push_back(c);
            j = j + 1;
        }
        k = k + 1;
        j = 1;
    }
    return resp;

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0; int i = 0;
    celda c; celda d;
    while (i < v.size()){
        c = buscoCeldaDeUnViaje(v[i], g);
        d = buscoCeldaDeUnViaje(buscoSiguientePunto(v,v[i]),g);
        if(abs(filaDeNombre(nombreDeCelda(c)) - filaDeNombre(nombreDeCelda(d))) >= 2
           || abs(columnaDeNombre(nombreDeCelda(c)) - columnaDeNombre(nombreDeCelda(d))) >= 2)
            resp = resp + 1;
        i = i + 1;
    }
    return resp;

}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    // codig

    return;
}