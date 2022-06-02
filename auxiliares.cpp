#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

double obtenerLatitud(gps posicion) {
    return get<0>(posicion);
}

double obtenerLongitud(gps posicion) {
    return get<1>(posicion);
}

gps obtenerPosicion(tuple<tiempo, gps> medicion) {
    return get<1>(medicion);
}

tiempo obtenerTiempo(tuple<tiempo, gps> medicion) {
    return get<0>(medicion);
}
double distEnKM(gps posicion1, gps posicion2) {
    double latitud1 = obtenerLatitud(posicion1);
    double latitud2 = obtenerLatitud(posicion2);
    double longitud1 = obtenerLongitud(posicion1);
    double longitud2 = obtenerLongitud(posicion2);

    // obtengo la distancia
    double distanciaLatitud = (latitud2 - latitud1) * pi / 180.0;
    double distanciaLongitud = (longitud2 - longitud1) * pi / 180.0;

    // paso las latitudes a radianes
    latitud1 = (latitud1) * pi / 180.0;
    latitud2 = (latitud2) * pi / 180.0;

    // aplico la formula
    double a = pow(sin(distanciaLatitud / 2), 2) +
               pow(sin(distanciaLongitud / 2), 2) *
               cos(latitud1) * cos(latitud2);

    double c = 2 * asin(sqrt(a));
    return radioTierra * c;
}

gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud){
    double lat = obtenerLatitud(p);
    double lon = obtenerLongitud(p);

    double dx = desvioMtsLatitud / 1000;
    double dy = desvioMtsLongitud / 1000;
    double new_latitude = lat + (dx / radioTierra) * (180 / pi);
    double new_longitude = lon + (dy / radioTierra) * (180 / pi) / cos(lat * pi / 180);
    return puntoGps(new_latitude, new_longitude);

}


gps puntoGps(double latitud, double longitud) {
    return make_tuple(latitud, longitud);
}

tuple<tiempo, gps> medicion(tiempo t, gps g) {
    return make_tuple(t, g);
}

void guardarGrillaEnArchivo(grilla g, string nombreArchivo){
    ofstream myfile;
    float esq1_lat, esq2_lat, esq1_lng, esq2_lng;
    int name_0, name_1;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < g.size(); i++){
        esq1_lat = get<0>(get<0>(g[i]));
        esq1_lng = get<1>(get<0>(g[i]));

        esq2_lat = get<0>(get<1>(g[i]));
        esq2_lng = get<1>(get<1>(g[i]));

        name_0 = get<0>(get<2>(g[i]));
        name_1 = get<1>(get<2>(g[i]));

        myfile << esq1_lat << "\t"
               << esq1_lng << "\t"
               << esq2_lat << "\t"
               << esq2_lng << "\t"
               << "(" << name_0 << "," << name_1 << ")"
               << endl;

    }
    myfile.close();

}

void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo){
    ofstream myfile;
    float lat, lng;

    myfile.open(nombreArchivo);
    myfile << std::fixed << std::setprecision(5);
    for(int i = 0; i < recorridos.size(); i++){
        for(int k = 0; k < recorridos[i].size(); k++){
            lat= get<0>(recorridos[i][k]);
            lng= get<1>(recorridos[i][k]);

            myfile << i << "\t"
                   << lat << "\t"
                   << lng << endl;
        }
    }
    myfile.close();

}

tiempo maxTiempo (viaje v){
    tiempo res = obtenerTiempo(v[0]);
    int i = 1;
    while (i < v.size()) {
        if ((obtenerTiempo(v[i]) > res)){
            res = obtenerTiempo(v[i]);
        }
        i = i + 1;
    }
    return res;
}

tiempo minTiempo (viaje v){
    tiempo res = obtenerTiempo(v[0]);
    int i = 1;
    while (i < v.size()) {
        if ((obtenerTiempo(v[i]) < res)){
            res = obtenerTiempo(v[i]);
        }
        i = i + 1;
    }
    return res;
}

tuple<tiempo,gps> buscoSiguientePunto(viaje v, tuple <tiempo, gps> tup){
    if (maxTiempo(v) == obtenerTiempo(tup))
        return tup;
    int i = 0; int k = 0; tuple<tiempo, gps> res;
    while (k < v.size()){
     if (obtenerTiempo(v[k]) == maxTiempo(v)) {
         res = v[k];
         k = v.size();
     }   
     k = k + 1;
    }
    while (i < v.size()){
        if (obtenerTiempo(v[i]) > obtenerTiempo(tup) && obtenerTiempo(v[i]) < obtenerTiempo(res))
            res = v[i];
        i = i + 1;
    }
    return res;
}

double velocidad(tuple <tiempo, gps> p1, tuple <tiempo, gps> p2){
    double vel = (distEnKM(obtenerPosicion(p1), obtenerPosicion(p2)))/((obtenerTiempo(p2) - obtenerTiempo(p1))/3600);
    return vel;
}

gps esq1DeCelda(celda c) {
    return get<0>(c);
}

gps esq2DeCelda(celda c) {
    return get<1>(c);
}

nombre nombreDeCelda(celda c){
    return get<2>(c);
}

int filaDeNombre(nombre n){
    return get<0>(n);
}

int columnaDeNombre(nombre n){
    return get<1>(n);
}

celda buscoCeldaDeUnViaje(tuple<tiempo, gps> v, grilla g){
    int k = 0; celda c;
    while (k < g.size()){
        if ((obtenerLatitud(obtenerPosicion(v)) <= obtenerLatitud(esq1DeCelda(g[k])))
            && (obtenerLongitud(obtenerPosicion(v)) <= obtenerLongitud(esq2DeCelda(g[k])))
            && (obtenerLatitud(obtenerPosicion(v)) >= obtenerLatitud(esq2DeCelda(g[k])))
            && (obtenerLongitud(obtenerPosicion(v)) >= obtenerLongitud(esq1DeCelda(g[k])))){
            c = g[k];
            k = g.size();
        }
        k = k + 1;
    }
    return c;
}
