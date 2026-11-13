#ifndef OBSTACULO_H
#define OBSTACULO_H

class Particula;

// Cuadrado estatico. (x, y) es la esquina inferior izquierda (eje y hacia arriba).
class Obstaculo {
private:
    double x, y;
    double lado;
    double e;         // coeficiente de restitucion

public:
    enum Lado { NINGUNO = -1, IZQUIERDO = 0, DERECHO = 1, INFERIOR = 2, SUPERIOR = 3 };

    Obstaculo(double x, double y, double lado, double e);

    int ladoImpacto(const Particula* p) const;  // que lado golpeo (o NINGUNO)
    bool rebotar(Particula* p);                 // v_perp' = -e*v_perp, v_par igual

    double getX() const { return x; }
    double getY() const { return y; }
    double getLado() const { return lado; }
    double getE() const { return e; }
};

#endif