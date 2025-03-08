#include "Simulation.h"
#include <sstream>
#include <fstream>
#include <cmath>
#include <iostream>
#include "tinyxml2.h"

using namespace tinyxml2;

// Функция физической симуляции
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity,
                                  double friction, bool collision, double restitution) {
    std::vector<double> positions;
    double position = startpos;
    double velocity = 0.0;
    double deltaTime = duration / steps;

    for (int i = 0; i < steps; ++i) {
        // Применяем гравитацию
        velocity += gravity * deltaTime;

        // Применяем трение
        velocity *= (1 - friction * deltaTime);

        // Обновляем позицию
        position += velocity * deltaTime;

        // Обработка столкновений (например, с "землёй" на уровне endpos)
        if (collision && ((startpos > endpos && position < endpos) ||
                          (startpos < endpos && position > endpos))) {
            position = endpos;
            velocity = -velocity * restitution;
        }

        positions.push_back(position);
    }
    return positions;
}

// Функция генерации CSS-анимации с использованием @keyframes
std::string generateCssAnimation(const std::vector<double>& positions, double duration, int steps) {
    std::ostringstream css;
    
    css << "@keyframes move {" << std::endl;
    // Для каждого шага генерируем ключевой кадр; процент вычисляем как i/(steps-1)*100
    for (int i = 0; i < steps; ++i) {
        double percent = (static_cast<double>(i) / (steps - 1)) * 100;
        css << "  " << percent << "% { transform: translateY(" << positions[i] << "px); }" << std::endl;
    }
    css << "}" << std::endl;
    
    css << "animation: move " << duration << "s linear;" << std::endl;
    
    return css.str();
}

// Функция загрузки ассета из XML-файла (используется tinyxml2)
std::vector<double> loadAsset(const std::string &filename) {
    std::vector<double> assetValues;
    XMLDocument doc;
    XMLError result = doc.LoadFile(filename.c_str());
    if (result != XML_SUCCESS) {
        std::cerr << "Ошибка загрузки XML файла: " << filename << std::endl;
        return assetValues;
    }
    XMLElement* root = doc.FirstChildElement("PMAsset");
    if (!root) {
        std::cerr << "Не найден корневой элемент <PMAsset> в " << filename << std::endl;
        return assetValues;
    }
    for (XMLElement* key = root->FirstChildElement("keyframe"); key != nullptr; key = key->NextSiblingElement("keyframe")) {
        double value = 0.0;
        key->QueryDoubleText(&value);
        assetValues.push_back(value);
    }
    return assetValues;
}

// Вспомогательная функция для вычисления среднего значения в диапазоне
double average(const std::vector<double>& values, int start, int end) {
    double sum = 0.0;
    int count = 0;
    for (int i = start; i <= end; ++i) {
        sum += values[i];
        count++;
    }
    return (count > 0) ? sum / count : 0.0;
}

// Генерация анимации на основе ассета
std::vector<double> runAssetSimulation(const std::vector<double>& assetKeyframes, int steps) {
    std::vector<double> positions;
    int m = assetKeyframes.size();
    if (m == 0) return positions;
    positions.reserve(steps);

    for (int i = 0; i < steps; ++i) {
        double t = static_cast<double>(i) / (steps - 1);
        if (t <= 0) {
            positions.push_back(assetKeyframes.front());
        } else if (t >= 1) {
            positions.push_back(assetKeyframes.back());
        } else {
            // Нормализуем индекс в ассете: index от 0 до m-1
            double index = t * (m - 1);
            int idx = static_cast<int>(std::floor(index));
            double f = index - idx;

            // Левая группа – от начала до idx
            double leftMean = average(assetKeyframes, 0, idx);
            // Правая группа – от idx+1 до конца (если есть)
            double rightMean = (idx + 1 < m) ? average(assetKeyframes, idx + 1, m - 1) : assetKeyframes.back();

            double outValue = (1 - f) * leftMean + f * rightMean;
            positions.push_back(outValue);
        }
    }

    return positions;
}
