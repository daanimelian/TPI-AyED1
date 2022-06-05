#ifndef TRANSPORTEURBANO_AUXILIARES_H
#define TRANSPORTEURBANO_AUXILIARES_H

#include "definiciones.h"
#include "string"

double obtenerLatitud(gps posicion);
double obtenerLongitud(gps posicion);
gps obtenerPosicion(tuple<tiempo, gps> medicion);
tiempo obtenerTiempo(tuple<tiempo, gps> medicion);
double distEnKM(gps posicion1, gps posicion2);
gps desviarPunto(gps p, double desvioMtsLatitud, double desvioMtsLongitud);
gps puntoGps(double latitud, double longitud);
tuple<tiempo, gps> medicion(tiempo t, gps g);

void guardarGrillaEnArchivo(grilla g, string nombreArchivo);
void guardarRecorridosEnArchivo(vector<recorrido> recorridos, string nombreArchivo);

tiempo maxTiempo (viaje v);
tiempo minTiempo (viaje v);
tuple<tiempo,gps> buscoSiguientePunto(viaje v, tuple <tiempo, gps> tup);
double velocidad(tuple <tiempo, gps> p1, tuple <tiempo, gps> p2);
gps esq1DeCelda(celda c);
gps esq2DeCelda(celda c);
nombre nombreDeCelda(celda c);
int filaDeNombre(nombre n);
int columnaDeNombre(nombre n);
celda buscoCeldaDeUnViaje(tuple<tiempo, gps> v, grilla g);
bool viajeEnFranjaHoraria(viaje v, tiempo t0, tiempo tf);

int puntoACorregir(viaje v, tiempo error);
tuple<tiempo, gps>  puntoInmediatoAnterior(tuple<tiempo, gps> punto, viaje v, vector<tiempo> errores);
tuple<tiempo, gps> puntoInmediatoPosterior(tuple<tiempo, gps> punto, viaje v, vector<tiempo> errores);
gps  gpsSobreRecta(tuple<tiempo, gps> punto_a, tuple<tiempo, gps> punto_b, tiempo tp_error);
bool estaSobreRecta(double x, double y, gps a, gps b);
bool tieneError(tuple<tiempo,gps> punto, vector<tiempo> errores);
#endif //TRANSPORTEURBANO_AUXILIARES_H
