#ifndef COLISION_H
#define COLISION_H

#include <string>

// Evento de colision. tipo: "pared", "obstaculo" o "fusion".
// idA = particula; idB = otra particula (fusion), indice del obstaculo
// (obstaculo) o -1 (pared).
class Colision {
private:
    double tiempo;
    std::string tipo;
    int idA, idB;

public:
    Colision(double tiempo, const std::string& tipo, int idA, int idB)
        : tiempo(tiempo), tipo(tipo), idA(idA), idB(idB) {}

    double getTiempo() const { return tiempo; }
    const std::string& getTipo() const { return tipo; }
    int getIdA() const { return idA; }
    int getIdB() const { return idB; }
};

#endif
