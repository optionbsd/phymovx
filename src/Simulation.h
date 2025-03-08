#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

// Функция для запуска симуляции движения.
// Если easeType не пустой, то позиция вычисляется по easing-интерполяции:
//   position = startpos + (endpos - startpos) * easing(progress, easeParam)
// В противном случае используется физическая модель с вычислением начальной скорости v0.
// Параметры:
//   steps     - количество шагов симуляции
//   duration  - общая длительность симуляции (в секундах)
//   startpos  - начальная позиция
//   endpos    - конечная позиция
//   gravity   - ускорение (используется только в физическом режиме)
//   easeType  - тип easing ("ease-in", "ease-out", "ease-in-out") или пустая строка для физического режима
//   easeParam - параметр, определяющий кривизну easing (например, степень), по умолчанию 2
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  const std::string& easeType = "", double easeParam = 2.0);

#endif // SIMULATION_H
