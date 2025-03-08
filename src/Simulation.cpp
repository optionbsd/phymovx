#include "Simulation.h"

// Здесь мы решаем уравнение движения:
// endpos = startpos + v0 * duration + 0.5 * gravity * duration^2
// Откуда v0 = (endpos - startpos - 0.5 * gravity * duration^2) / duration

std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity) {
    std::vector<double> positions;
    positions.reserve(steps);
    
    double T = duration;
    double v0 = (endpos - startpos - 0.5 * gravity * T * T) / T;
    
    // Интервал времени между шагами
    double dt = T / (steps - 1);
    
    for (int i = 0; i < steps; ++i) {
        double t = dt * i;
        double pos = startpos + v0 * t + 0.5 * gravity * t * t;
        positions.push_back(pos);
    }
    
    return positions;
}
