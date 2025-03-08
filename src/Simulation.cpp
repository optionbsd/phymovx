#include "Simulation.h"
#include <cmath>

// Функции easing
static double easeIn(double p, double easeParam) {
    return std::pow(p, easeParam);
}

static double easeOut(double p, double easeParam) {
    return 1.0 - std::pow(1.0 - p, easeParam);
}

static double easeInOut(double p, double easeParam) {
    if (p < 0.5)
        return 0.5 * std::pow(2 * p, easeParam);
    else
        return 1.0 - 0.5 * std::pow(2 * (1 - p), easeParam);
}

std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  const std::string& easeType, double easeParam,
                                  double friction, bool collision, double restitution) {
    std::vector<double> positions;
    positions.reserve(steps);

    double dt = duration / (steps - 1);

    // Режим easing: используется интерполяция между startpos и endpos.
    if (!easeType.empty()) {
        for (int i = 0; i < steps; ++i) {
            double t = dt * i;
            double p = t / duration;
            double f = p;
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
    }
    // Если включена фрикция или столкновения, используем интеграционный метод (явный метод Эйлера).
    else if (friction > 0.0 || collision) {
        // Вычисляем начальную скорость по формуле для свободного падения (без учета фрикции и столкновений)
        double T = duration;
        double v0 = (endpos - startpos - 0.5 * gravity * T * T) / T;
        double x = startpos;
        double v = v0;
        for (int i = 0; i < steps; ++i) {
            positions.push_back(x);
            // Расчет ускорения: гравитация плюс трение, которое всегда действует против направления движения
            double a = gravity;
            if (v != 0)
                a += -friction * (v > 0 ? 1.0 : -1.0);
            
            // Обновляем скорость и позицию
            v += a * dt;
            x += v * dt;
            
            // Если включены столкновения, проверяем выход за пределы.
            // Предполагаем, что если startpos > endpos, то endpos является "полом"
            if (collision) {
                if (startpos > endpos && x < endpos) {
                    x = endpos;
                    v = -v * restitution;
                } else if (startpos < endpos && x > endpos) {
                    x = endpos;
                    v = -v * restitution;
                }
            }
        }
    }
    // Физическая модель без фрикции и столкновений (аналитическое решение)
    else {
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
