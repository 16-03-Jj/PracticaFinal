#include "Simulacion.h"
#include <cmath>
#include <iostream>

Simulacion::Simulacion(double dt, int pasos, const Caja& caja, const std::string& archivoSalida)
    : dt(dt), tiempo(0.0), pasos(pasos), caja(caja), registro(archivoSalida) {}

void Simulacion::agregarParticula(const Particula& p) { particulas.push_back(p); }

void Simulacion::inicializar() {
    if (!registro.abrir()) {
        std::cerr << "No se pudo abrir el archivo de salida\n";
        return;
    }
    registro.guardarEscenario(caja);
    registro.guardarPosiciones(tiempo, particulas);   // t = 0
}

// Orden en cada paso: fusiones -> paredes -> obstaculos.
void Simulacion::detectarColisiones() {
    // 3. Particula-particula (completamente inelastica). Se repite mientras haya
    //    fusiones, porque el cuerpo nuevo tiene mayor radio y puede tocar a otro.
    bool huboFusion = true;
    while (huboFusion) {
        huboFusion = false;
        for (size_t i = 0; i < particulas.size() && !huboFusion; ++i) {
            if (!particulas[i].estaActiva()) continue;
            for (size_t j = i + 1; j < particulas.size(); ++j) {
                if (!particulas[j].estaActiva()) continue;
                double dx = particulas[i].getX() - particulas[j].getX();
                double dy = particulas[i].getY() - particulas[j].getY();
                double rr = particulas[i].getRadio() + particulas[j].getRadio();
                if (dx * dx + dy * dy <= rr * rr) {
                    colisiones.emplace_back(tiempo, "fusion",
                                            particulas[i].getId(), particulas[j].getId());
                    registro.guardarColision(colisiones.back());
                    particulas[i].fusionar(&particulas[j]);
                    huboFusion = true;
                    break;
                }
            }
        }
    }

    for (Particula& p : particulas) {
        if (!p.estaActiva()) continue;

        // 1. Particula-pared (perfectamente elastica)
        if (caja.rebotarPared(&p)) {
            colisiones.emplace_back(tiempo, "pared", p.getId(), -1);
            registro.guardarColision(colisiones.back());
        }

        // 2. Particula-obstaculo (inelastica, coeficiente e)
        std::vector<Obstaculo>& obs = caja.getObstaculos();
        for (size_t k = 0; k < obs.size(); ++k) {
            if (obs[k].rebotar(&p)) {
                colisiones.emplace_back(tiempo, "obstaculo", p.getId(), static_cast<int>(k));
                registro.guardarColision(colisiones.back());
            }
        }
    }
}

void Simulacion::paso() {
    for (Particula& p : particulas)
        if (p.estaActiva()) p.mover(dt);

    tiempo += dt;
    detectarColisiones();
    registro.guardarPosiciones(tiempo, particulas);
}

void Simulacion::ejecutar() {
    inicializar();

    double e0 = 0;
    for (const Particula& p : particulas) e0 += p.energiaCinetica();

    for (int k = 0; k < pasos; ++k) paso();
    registro.cerrar();

    double ef = 0;
    int activas = 0, nPared = 0, nObst = 0, nFus = 0;
    for (const Particula& p : particulas)
        if (p.estaActiva()) { ef += p.energiaCinetica(); ++activas; }
    for (const Colision& c : colisiones) {
        if (c.getTipo() == "pared") ++nPared;
        else if (c.getTipo() == "obstaculo") ++nObst;
        else ++nFus;
    }

    std::cout << "Simulacion terminada (t = " << tiempo << ")\n"
              << "Colisiones -> pared: " << nPared << ", obstaculo: " << nObst
              << ", fusion: " << nFus << "\n"
              << "Particulas activas: " << activas << " de " << particulas.size() << "\n"
              << "Energia cinetica inicial: " << e0 << "  final: " << ef << "\n";
}