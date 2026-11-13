#include "RegistroSalida.h"
#include <iomanip>

RegistroSalida::RegistroSalida(const std::string& nombre) : nombre(nombre) {}

bool RegistroSalida::abrir() {
    archivo.open(nombre);
    archivo << std::fixed << std::setprecision(4);
    return archivo.is_open();
}

void RegistroSalida::guardarEscenario(const Caja& caja) {
    archivo << "CAJA," << caja.getAncho() << "," << caja.getAlto() << "\n";
    for (const Obstaculo& o : caja.getObstaculos())
        archivo << "OBST," << o.getX() << "," << o.getY() << "," << o.getLado() << "\n";
}

void RegistroSalida::guardarPosiciones(double t, const std::vector<Particula>& ps) {
    for (const Particula& p : ps)
        if (p.estaActiva())
            archivo << "POS," << t << "," << p.getId() << ","
                    << p.getX() << "," << p.getY() << "," << p.getRadio() << "\n";
}

void RegistroSalida::guardarColision(const Colision& c) {
    archivo << "COL," << c.getTiempo() << "," << c.getTipo() << ","
            << c.getIdA() << "," << c.getIdB() << "\n";
}

void RegistroSalida::cerrar() {
    if (archivo.is_open()) archivo.close();
}
