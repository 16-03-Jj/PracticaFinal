#include "Particula.h"
#include <cmath>

Particula::Particula(int id, double x, double y, double vx, double vy,
                     double masa, double radio)
    : id(id), x(x), y(y), vx(vx), vy(vy), masa(masa), radio(radio), activa(true) {}

void Particula::mover(double dt) {
    x += vx * dt;
    y += vy * dt;
}

// Colision completamente inelastica: esta particula absorbe a "otra".
//  - velocidad: v' = (m1*v1 + m2*v2) / (m1 + m2)   (conservacion del momento)
//  - posicion : centro de masa de ambas
//  - radio    : se conserva el area  -> r' = sqrt(r1^2 + r2^2)
void Particula::fusionar(Particula* otra) {
    double M = masa + otra->masa;
    double nvx = (masa * vx + otra->masa * otra->vx) / M;
    double nvy = (masa * vy + otra->masa * otra->vy) / M;
    double nx = (masa * x + otra->masa * otra->x) / M;
    double ny = (masa * y + otra->masa * otra->y) / M;

    radio = std::sqrt(radio * radio + otra->radio * otra->radio);
    masa = M;
    vx = nvx; vy = nvy;
    x = nx;   y = ny;

    otra->activa = false;
}

double Particula::energiaCinetica() const {
    return 0.5 * masa * (vx * vx + vy * vy);
}
