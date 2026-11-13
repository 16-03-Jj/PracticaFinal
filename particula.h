#ifndef PARTICULA_H
#define PARTICULA_H

class Particula {
private:
    int id;
    double x, y;      // posicion del centro
    double vx, vy;    // velocidad
    double masa;
    double radio;
    bool activa;      // false cuando fue absorbida por una fusion

public:
    Particula(int id, double x, double y, double vx, double vy,
              double masa, double radio);

    void mover(double dt);                  // x += vx*dt, y += vy*dt
    void fusionar(Particula* otra);         // colision completamente inelastica
    double energiaCinetica() const;

    int getId() const { return id; }
    double getX() const { return x; }
    double getY() const { return y; }
    double getVx() const { return vx; }
    double getVy() const { return vy; }
    double getMasa() const { return masa; }
    double getRadio() const { return radio; }
    bool estaActiva() const { return activa; }

    void setX(double nx) { x = nx; }
    void setY(double ny) { y = ny; }
    void setVx(double nvx) { vx = nvx; }
    void setVy(double nvy) { vy = nvy; }
};

#endif
