#include "Obstaculo.h"
#include "Particula.h"
#include <cmath>
#include <algorithm>

Obstaculo::Obstaculo(double x, double y, double lado, double e)
    : x(x), y(y), lado(lado), e(e) {}

// Punto del cuadrado mas cercano al centro de la particula: si esta a menos
// de "radio", hay colision. El lado se decide con el vector (dx, dy) que va
// de ese punto al centro (en esquinas gana la componente mayor).
int Obstaculo::ladoImpacto(const Particula* p) const {
    double px = p->getX(), py = p->getY(), r = p->getRadio();
    double cx = std::clamp(px, x, x + lado);
    double cy = std::clamp(py, y, y + lado);
    double dx = px - cx, dy = py - cy;

    if (dx * dx + dy * dy >= r * r) return NINGUNO;

    if (dx == 0.0 && dy == 0.0) {   // centro dentro del cuadrado: lado mas cercano
        double d[4] = { px - x, x + lado - px, py - y, y + lado - py };
        return static_cast<int>(std::min_element(d, d + 4) - d);
    }
    if (std::fabs(dx) > std::fabs(dy)) return dx < 0 ? IZQUIERDO : DERECHO;
    return dy < 0 ? INFERIOR : SUPERIOR;
}

bool Obstaculo::rebotar(Particula* p) {
    int l = ladoImpacto(p);
    if (l == NINGUNO) return false;

    double nx = 0, ny = 0, r = p->getRadio();
    switch (l) {
    case IZQUIERDO: nx = -1; p->setX(x - r);        break;
    case DERECHO:   nx =  1; p->setX(x + lado + r); break;
    case INFERIOR:  ny = -1; p->setY(y - r);        break;
    case SUPERIOR:  ny =  1; p->setY(y + lado + r); break;
    }

    // vn = componente de v sobre la normal del lado golpeado
    double vn = p->getVx() * nx + p->getVy() * ny;
    if (vn >= 0) return false;   // ya se aleja: no es un nuevo choque

    // v' = v_par + (-e) v_perp = v - (1 + e) * vn * n
    p->setVx(p->getVx() - (1.0 + e) * vn * nx);
    p->setVy(p->getVy() - (1.0 + e) * vn * ny);
    return true;
}
