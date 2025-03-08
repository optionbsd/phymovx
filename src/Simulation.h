#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <string>

// Функция физической симуляции (с учётом гравитации, трения, столкновений и restitution)
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  double friction, bool collision, double restitution);

// Функция генерации CSS-анимации из последовательности значений
std::string generateCssAnimation(const std::vector<double>& positions, double duration, int steps);

// Функция загрузки ассета из XML-файла (используется tinyxml2)
std::vector<double> loadAsset(const std::string &filename);

// Функция генерации анимации на основе ассета
// Для каждого выходного шага (t от 0 до 1) вычисляем значение по формуле:
//    если t == 0 => output = asset[0]
//    если t == 1 => output = asset[m-1]
//    иначе: индекс = t*(m-1), i = floor(индекса), f = дробная часть,
//         leftMean = среднее по asset[0..i],
//         rightMean = среднее по asset[i+1..m-1],
//         output = (1-f)*leftMean + f*rightMean.
std::vector<double> runAssetSimulation(const std::vector<double>& assetKeyframes, int steps);

#endif // SIMULATION_H
