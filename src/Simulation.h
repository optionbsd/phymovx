#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

// Функция для запуска симуляции движения.
// Если easeType не пустой, то позиция вычисляется по easing-интерполяции:
//    position = startpos + (endpos - startpos) * easing(progress, easeParam)
// Если же включены фрикция или столкновения, используется интеграция методом Эйлера.
// Параметры:
//   steps        - количество шагов симуляции
//   duration     - общая длительность симуляции (сек)
//   startpos     - начальная позиция
//   endpos       - конечная позиция (также может использоваться как граница для столкновения)
//   gravity      - ускорение (м/с²)
//   easeType     - тип easing ("ease-in", "ease-out", "ease-in-out") или пустая строка для физического режима
//   easeParam    - параметр для easing (например, степень), по умолчанию 2
//   friction     - коэффициент трения (м/с²), по умолчанию 0 (отсутствие трения)
//   collision    - включение столкновений (true/false)
//   restitution  - коэффициент упругости столкновения (по умолчанию 1)
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  const std::string& easeType = "", double easeParam = 2.0,
                                  double friction = 0.0, bool collision = false, double restitution = 1.0);

#endif // SIMULATION_H
