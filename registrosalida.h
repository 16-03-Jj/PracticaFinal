#ifndef REGISTROSALIDA_H
#define REGISTROSALIDA_H

#include <fstream>
#include <string>
#include <vector>
#include "Particula.h"
#include "Colision.h"
#include "Caja.h"

// Escribe el archivo de texto (CSV por lineas con prefijo):
//   CAJA,ancho,alto
//   OBST,x,y,lado
//   POS,t,id,x,y,radio      (una por particula activa y por paso)
//   COL,t,tipo,idA,idB
class RegistroSalida {
private:
    std::string nombre;
    std::ofstream archivo;

public:
    RegistroSalida(const std::string& nombre);

    bool abrir();
    void guardarEscenario(const Caja& caja);
    void guardarPosiciones(double t, const std::vector<Particula>& particulas);
    void guardarColision(const Colision& c);
    void cerrar();
};

#endif
