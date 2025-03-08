#include "Simulation.h"
#include <cmath>

// Функции easing
// ease-in: прогресс p преобразуется как p^easeParam
static double easeIn(double p, double easeParam) {
    return std::pow(p, easeParam);
}

// ease-out: прогресс p преобразуется как 1 - (1 - p)^easeParam
static double easeOut(double p, double easeParam) {
    return 1.0 - std::pow(1.0 - p, easeParam);
}

// ease-in-out: комбинированная функция
static double easeInOut(double p, double easeParam) {
    if (p < 0.5) {
        return 0.5 * std::pow(2 * p, easeParam);
    } else {
        return 1.0 - 0.5 * std::pow(2 * (1 - p), easeParam);
    }
}

std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  const std::string& easeType, double easeParam) {
    std::vector<double> positions;
    positions.reserve(steps);

    // Расчет временного шага
    double dt = duration / (steps - 1);

    // Если указан режим easing, то используем интерполяцию между startpos и endpos.
    if (!easeType.empty()) {
        for (int i = 0; i < steps; ++i) {
            double t = dt * i;
            double p = t / duration; // нормированный прогресс от 0 до 1
            double f = p; // по умолчанию линейная интерполяция
            if (easeType == "ease-in") {
                f = easeIn(p, easeParam);
            } else if (easeType == "ease-out") {
                f = easeOut(p, easeParam);
            } else if (easeType == "ease-in-out") {
                f = easeInOut(p, easeParam);
            }
            double pos = startpos + (endpos - startpos) * f;
            positions.push_back(pos);
        }
    } else {
        // Физическая модель: рассчитываем начальную скорость по уравнению:
        // endpos = startpos + v0 * duration + 0.5 * gravity * duration^2
        double T = duration;
        double v0 = (endpos - startpos - 0.5 * gravity * T * T) / T;
        for (int i = 0; i < steps; ++i) {
            double t = dt * i;
            double pos = startpos + v0 * t + 0.5 * gravity * t * t;
            positions.push_back(pos);
        }
    }
    
    return positions;
}
