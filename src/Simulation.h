#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>

// Функция для запуска симуляции движения.
// Параметры:
//   steps     - количество шагов симуляции
//   duration  - общая длительность симуляции (в секундах)
//   startpos  - начальная позиция
//   endpos    - конечная позиция
//   gravity   - ускорение (например, 9.807)
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity);

#endif // SIMULATION_H
