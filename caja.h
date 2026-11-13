#ifndef CAJA_H
#define CAJA_H

#include <vector>
#include "Obstaculo.h"

class Particula;

// Region rectangular [0, ancho] x [0, alto] que contiene los obstaculos.
class Caja {
private:
    double ancho, alto;
    std::vector<Obstaculo> obstaculos;

public:
    Caja(double ancho, double alto);

    void agregarObstaculo(const Obstaculo& o);
    bool rebotarPared(Particula* p);          // rebote perfectamente elastico
    bool contiene(double x, double y) const;

    double getAncho() const { return ancho; }
    double getAlto() const { return alto; }
    std::vector<Obstaculo>& getObstaculos() { return obstaculos; }
    const std::vector<Obstaculo>& getObstaculos() const { return obstaculos; }
};

#endif
