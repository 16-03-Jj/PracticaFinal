#include "Caja.h"
#include "Particula.h"
#include <cmath>

Caja::Caja(double ancho, double alto) : ancho(ancho), alto(alto) {}

void Caja::agregarObstaculo(const Obstaculo& o) { obstaculos.push_back(o); }

bool Caja::contiene(double x, double y) const {
    return x >= 0 && x <= ancho && y >= 0 && y <= alto;
}

// Se invierte solo la componente perpendicular a la pared (|e| = 1): la energia
// cinetica se conserva.
bool Caja::rebotarPared(Particula* p) {
    bool choco = false;
    double r = p->getRadio();

    if (p->getX() - r < 0) {
        p->setX(r);
        p->setVx(std::fabs(p->getVx()));
        choco = true;
    } else if (p->getX() + r > ancho) {
        p->setX(ancho - r);
        p->setVx(-std::fabs(p->getVx()));
        choco = true;
    }
    if (p->getY() - r < 0) {
        p->setY(r);
        p->setVy(std::fabs(p->getVy()));
        choco = true;
    } else if (p->getY() + r > alto) {
        p->setY(alto - r);
        p->setVy(-std::fabs(p->getVy()));
        choco = true;
    }
    return choco;
}