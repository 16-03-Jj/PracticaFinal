#include "Simulacion.h"

int main() {
    const double e = 0.7;   // coeficiente de restitucion de los obstaculos

    // Caja de 800 x 600 con 4 obstaculos cuadrados de lado 80
    Caja caja(800.0, 600.0);
    caja.agregarObstaculo(Obstaculo(150, 400, 80, e));
    caja.agregarObstaculo(Obstaculo(570, 400, 80, e));
    caja.agregarObstaculo(Obstaculo(150, 120, 80, e));
    caja.agregarObstaculo(Obstaculo(570, 120, 80, e));

    Simulacion sim(0.005, 4000, caja, "salida.txt");

    //                      id    x     y     vx     vy   masa radio
    sim.agregarParticula(Particula(1, 100, 300,  120,   40, 1.0, 10));
    sim.agregarParticula(Particula(2, 700, 300, -100,   30, 2.0, 12));
    sim.agregarParticula(Particula(3, 400, 520,   30, -110, 1.5, 10));
    sim.agregarParticula(Particula(4, 400,  80,  -40,   90, 1.0,  8));
    sim.agregarParticula(Particula(5, 400, 300,   60,   60, 2.0, 12));

    sim.ejecutar();
    return 0;
}