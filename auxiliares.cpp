#include <algorithm>
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

const double pi = 3.14;
double radioTierra = 6378;

bool gpsValido(gps posicion){
    bool es_valido = false;
    double latitud = obtenerLatitud(posicion);
    double longitud = obtenerLongitud(posicion);
    if ((-90<=latitud && latitud<=90) && (-180<=longitud && longitud<=180) ){

        es_valido = true;
    }
    return es_valido;
}
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
    int i = 0; tuple<tiempo, gps> res = v[v.size()-1];
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
bool viajeEnFranjaHoraria(viaje v, tiempo t0, tiempo tf){
    bool res;
    if ((minTiempo(v) > t0 && maxTiempo(v) < tf)
    || (minTiempo(v) < t0 && maxTiempo(v) > t0 )
    || (minTiempo(v) < tf && maxTiempo(v) > tf)
    || (minTiempo(v) < t0 && maxTiempo(v) > tf)){
        res = true;
    } else{
        res = false;
    }

    return res;
}

bool gpsCorrecto(viaje v, int i, vector<tiempo> errores){
    bool es_correcto = true;
    int j = 0;
    while (j < errores.size() && es_correcto){
        if (errores[j] == get<0>(v[i])){
            es_correcto = false;
        }
    }
    return es_correcto;
}

bool gpsSobreRecta(gps x, gps a, gps b){
    bool esta = false;
    double recta = (((get<1>(a) - get<1>(b)) / (get<0>(a) - get<0>(b))) * get<0>(x)) + (((get<1>(b)*get<0>(a)) - (get<1>(a)*get<0>(b))) / (get<0>(a) - get<0>(b)));
    if ((get<0>(a) != get<0>(b) && (get<1>(x) == recta)) || ((get<0>(a) == get<0>(b)) && (get<1>(a) == get<1>(b)))){
        esta = true;
    }
    return esta;
}

bool losDosPuntosMasCercanos(viaje v, int k, int p, int q){
    bool mas_cercano = true;
    int i = 0;

    while (i < v.size() && mas_cercano){
        if ((i != k) && (i !=  p) && (i !=  q)){
            if (!((distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[k])) > distEnKM(obtenerPosicion(v[p]), obtenerPosicion(v[k]))) && (distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[k])) > distEnKM(obtenerPosicion(v[q]), obtenerPosicion(v[k])))  )){
                mas_cercano = false;
            }
        }
        i ++;
    }

    return  mas_cercano;
}

bool moduloCorrectoProporcionaVelocidad(viaje v, int k, int p, int q){
    bool proporciona_velocidad = false;
    double dis_entre_k_p = distEnKM(obtenerPosicion(v[k]), obtenerPosicion(v[p]));
    double dis_entre_p_q = distEnKM(obtenerPosicion(v[p]), obtenerPosicion(v[q]));
    double tiempo = (obtenerTiempo(v[k]) - obtenerTiempo(v[q]))/(obtenerTiempo(v[k]) - obtenerTiempo(v[p]));
    if (dis_entre_k_p == (dis_entre_p_q * tiempo)){
        proporciona_velocidad = true;
    }
    return proporciona_velocidad;
}

bool correctoRespectoPivot(tiempo tp, tiempo tk, int xp, int xk){
    bool correcto= false;

    if (abs(tp -tk) == abs(xp - xk)){
        correcto = true;
    }

    return correcto;
}
bool noEstaEnErrores(tiempo t, vector<tiempo> errores){
    bool esta = false;
    int i = 0;
    while ( (i < errores.size()) && !esta){
        if (t == errores[i]){
            esta = true;
        }
    }
    return  esta;
}

bool losCorrectosNoCambian(viaje v, viaje v_prev, vector<tiempo> errores){
    bool no_cambia;
    int i =0;
    while (i < v.size() && no_cambia) {
        if ((v[i] == v_prev[i]) && noEstaEnErrores(obtenerTiempo(v_prev[i]), errores)){
            no_cambia = true;
        } else{
            no_cambia = false;
        }

        i++;
    }

    return no_cambia;
}

bool posicionEnInstanteT(tuple<tiempo, gps> v, tiempo t){
    bool en_posicion = false;
    if (obtenerTiempo(v) == t){
        en_posicion = true;
    }

    return en_posicion;
}
bool correctoEnRectaVertical(viaje v, int k, int p, int q){
    gps posicion_p = obtenerPosicion(v[p]);
    gps posicion_q = obtenerPosicion(v[q]);
    gps posicion_k = obtenerPosicion(v[k]);
    return ((obtenerLatitud(posicion_p) == obtenerLatitud(posicion_q)) && correctoRespectoPivot(obtenerTiempo(v[p]),obtenerTiempo(v[k]), obtenerLongitud(posicion_p), obtenerLongitud(posicion_k)));

}
bool correctoEnRectaOrdinaria(viaje v, int k, int p, int q) {
    gps posicion_p = obtenerPosicion(v[p]);
    gps posicion_q = obtenerPosicion(v[q]);
    gps posicion_k = obtenerPosicion(v[k]);
    return ((obtenerLatitud(posicion_p) < obtenerLatitud(posicion_q)) && correctoRespectoPivot(obtenerTiempo(v[p]),obtenerTiempo(v[k]),
                                                                                  obtenerLatitud(posicion_p), obtenerLatitud(posicion_k)));
}
bool posicionCorrectaEnRecta(viaje v, int k, int p, int q){
    return correctoEnRectaOrdinaria(v,k,p,q) || correctoEnRectaVertical(v,k,p,q);
}
bool gpsProporcionalVelocidad(viaje v, int k, int p, int q){
    return moduloCorrectoProporcionaVelocidad(v,k,p,q) && posicionCorrectaEnRecta(v,k,p,q);
}
tuple<tiempo, gps> puntoCorrespondienteAError(viaje v, tiempo error){

    tuple<tiempo,gps> punto;

    for (int i = 0; i < v.size(); ++i) {

        if (obtenerTiempo(v[i]) == error){
            punto = v[i];
        }
    }
    return punto;
}
bool gpsCorregido(tuple<tiempo,gps> punto, viaje v, vector<tiempo> errores){
    int k;
    bool esta_corregido = false;

    for (int i = 0; i < v.size(); ++i) {
        if(v[i] == punto){
            k = i;
        }
    }

    for (int i = 0; i < v.size() && !esta_corregido; ++i) {
        for (int j = 0; j < v.size() && !esta_corregido; ++j) {
            if (losDosPuntosMasCercanos(v, k, i, j) && gpsCorrecto(v,i,errores) && gpsCorrecto(v,j,errores) && gpsSobreRecta(obtenerPosicion(punto), obtenerPosicion(v[i]), obtenerPosicion(v[j])) &&
                    gpsProporcionalVelocidad(v, k, i, j)){
                    esta_corregido = true;
            }
        }

    }
    return esta_corregido;
}
bool todosErroresCorregidos(viaje v, vector<tiempo> errores){
    bool corregido = true;
    int i = 0;
   while( i < errores.size() && corregido) {
        tuple<tiempo,gps> punto = puntoCorrespondienteAError(v, errores[i]);
       if (!(posicionEnInstanteT(punto, errores[i]) && gpsCorregido(punto, errores) && gpsValido(obtenerPosicion(punto)))){
             corregido = false;
       }

       i++;
    }
   return corregido;
}


