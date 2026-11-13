#ifndef SIMULACION_H
#define SIMULACION_H

#include <string>
#include <vector>
#include "Caja.h"
#include "Particula.h"
#include "Colision.h"
#include "RegistroSalida.h"

class Simulacion {
private:
    double dt;
    double tiempo;
    int pasos;
    Caja caja;
    std::vector<Particula> particulas;   // las absorbidas quedan con activa=false
    std::vector<Colision> colisiones;
    RegistroSalida registro;

public:
    Simulacion(double dt, int pasos, const Caja& caja, const std::string& archivoSalida);

    void agregarParticula(const Particula& p);
    void inicializar();
    void paso();
    void detectarColisiones();
    void ejecutar();
};

#endif
