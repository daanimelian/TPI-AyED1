#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tiempoTotal(viaje v) {
    tiempo t = maxTiempo(v) - minTiempo(v);;
    return t;
}

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
distancia distanciaTotal(viaje v) {
    distancia d;
    int i = 0;
    while (i < v.size()){
        d = d + (distEnKM(obtenerPosicion(v[i]), obtenerPosicion(buscoSiguientePunto(v, v[i]))));
        i++;
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
        i++;
    }

    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/
vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp = {};
    int i = 0, k = 0;
    bool estaDentro = false;
    while (k < r.size()){
        while (i < v.size()){
            if (distEnKM(obtenerPosicion(v[i]), r[k]) < u) {
                estaDentro = true;
                i = v.size();
            }
            i++;
        }
        if (!estaDentro){
            resp.push_back(r[k]);
        }
        i = 0;
        k ++ ;
        estaDentro = false;
    }

    return resp;
}

/***************************************** EJERCICIO flota ***************************************/
int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp = 0;
    int i = 0;
    while (i < f.size()){
        if (viajeEnFranjaHoraria(f[i], t0, tf)) // achicar esto
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
                 (minlongitud + ((j - 1)* ((maxlongitud - minlongitud) / m)))};
            b = {(maxlatitud - k * ((maxlatitud - minlatitud) / n)),
                 (minlongitud + (j * ((maxlongitud - minlongitud) / m)))};
            c = {a, b, {k, j}};
            resp.push_back(c);
            j = j + 1;
        }
        k = k + 1;
        j = 1;
    }

    return resp;
}

/************************************* EJERCICIO cantidadDeSaltos ******************************/
int cantidadDeSaltos(grilla g, viaje v) {
    int resp = 0, i = 0;
    celda c, d;
    while (i < v.size()){
        c = buscoCeldaDeUnViaje(v[i], g);
        d = buscoCeldaDeUnViaje(buscoSiguientePunto(v,v[i]),g);
        if (sqrt(pow((filaDeNombre(nombreDeCelda(c)) - filaDeNombre(nombreDeCelda(d))),2) +
                 pow((columnaDeNombre(nombreDeCelda(c))- columnaDeNombre(nombreDeCelda(d))),2)) > 1)
            resp = resp + 1;
        i = i + 1;
    }
    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/
void corregirViaje(viaje& v, vector<tiempo> errores){
    tuple<tiempo, gps> punto_a, punto_b;
    gps gps_corregido;
    for (int i = 0; i < errores.size(); ++i) {
        int indice = puntoACorregir(v, errores[i]);
        if ((indice !=0) && (indice != v.size()-1)){
            punto_a = puntoInmediatoAnterior(v[indice], v, errores);
            punto_b = puntoInmediatoPosterior(v[indice], v, errores);
            gps_corregido = gpsSobreRecta(punto_a, punto_b, errores[i]);
        }
        else if (indice == 0){
            punto_a  = puntoInmediatoPosterior(v[indice], v, errores);
            punto_b  = puntoInmediatoPosterior(punto_a, v, errores);
            gps_corregido = gpsSobreRecta(punto_a, punto_b, errores[i]);
        } else{
            punto_a = puntoInmediatoAnterior(v[indice], v, errores);
            punto_b = puntoInmediatoAnterior(punto_a, v, errores);
            gps_corregido = gpsSobreRecta(punto_a, punto_b, errores[i]);
        }

        v[indice] = make_tuple(errores[i], gps_corregido);
    }

    return;
}
