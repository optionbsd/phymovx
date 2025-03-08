#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

// Функция для преобразования строки с суффиксом "s" в секунды (например, "1s")
double parseDuration(const std::string& durationStr) {
    std::istringstream iss(durationStr);
    double value;
    iss >> value;
    return value; // предполагаем, что суффикс "s" просто опускается
}

// Структура для параметров командной строки
struct CmdOptions {
    int steps = 0;
    double duration = 0.0;
    double startpos = 0.0;
    double endpos = 0.0;
    double gravity = 0.0;
    double friction = 0.0;
    bool collision = false;
    double restitution = 1.0;
    std::string outputType = "json"; // тип вывода: "json" или "css"
};

// Функция для вычисления положения с учётом параметров
std::vector<double> runSimulation(int steps, double duration, double startpos, double endpos, double gravity, double friction, bool collision, double restitution) {
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

        // Если есть столкновение (например, с землёй)
        if (collision && position <= 0) {
            position = 0; // объект не может быть ниже нуля
            velocity = -velocity * restitution; // отскок с коэффициентом упругости
        }

        // Добавляем значение позиции в результат
        positions.push_back(position);

        // Если объект достиг цели, можем завершить симуляцию
        if (position <= endpos) break;
    }

    return positions;
}

// Простейший парсер командной строки
CmdOptions parseArguments(int argc, char* argv[]) {
    CmdOptions opts;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-steps" && i+1 < argc) {
            opts.steps = std::stoi(argv[++i]);
        } else if (arg == "-duration" && i+1 < argc) {
            opts.duration = parseDuration(argv[++i]);
        } else if (arg == "-startpos" && i+1 < argc) {
            opts.startpos = std::stod(argv[++i]);
        } else if (arg == "-endpos" && i+1 < argc) {
            opts.endpos = std::stod(argv[++i]);
        } else if (arg == "-gravity" && i+1 < argc) {
            opts.gravity = std::stod(argv[++i]);
        } else if (arg == "-friction" && i+1 < argc) {
            opts.friction = std::stod(argv[++i]);
        } else if (arg == "-collision" && i+1 < argc) {
            std::string col = argv[++i];
            opts.collision = (col == "true" || col == "1");
        } else if (arg == "-restitution" && i+1 < argc) {
            opts.restitution = std::stod(argv[++i]);
        } else if (arg == "-output" && i+1 < argc) {
            opts.outputType = argv[++i]; // "json" или "css"
        }
    }
    return opts;
}

// Функция для генерации CSS анимации с позициями на каждом шаге
std::string generateCssAnimation(const std::vector<double>& positions, double duration, int steps) {
    std::ostringstream css;
    
    // Начинаем с создания @keyframes
    css << "@keyframes move {" << std::endl;

    // Генерация ключевых кадров для каждого шага
    for (int i = 0; i < steps; ++i) {
        double time = (static_cast<double>(i) / (steps - 1)) * 100; // вычисляем процент времени для шага
        css << "  " << time << "% { transform: translateY(" << positions[i] << "px); }" << std::endl;
    }

    css << "}" << std::endl;

    // Генерация правила для анимации
    css << "transition: all " << duration << "s steps(" << steps << ", end);" << std::endl;
    css << "animation: move " << duration << "s steps(" << steps << ") infinite;" << std::endl;

    return css.str();
}

int main(int argc, char* argv[]) {
    CmdOptions options = parseArguments(argc, argv);

    if(options.steps <= 0 || options.duration <= 0.0) {
        std::cerr << "Необходимо указать корректное число шагов и длительность." << std::endl;
        return 1;
    }
    
    // Выполняем симуляцию
    std::vector<double> positions = runSimulation(
        options.steps, 
        options.duration, 
        options.startpos, 
        options.endpos, 
        options.gravity,
        options.friction,
        options.collision,
        options.restitution
    );

    // Вывод в зависимости от выбранного формата
    if (options.outputType == "css") {
        // Генерация CSS анимации
        std::cout << generateCssAnimation(positions, options.duration, options.steps) << std::endl;
    } else {
        // Вывод в формате JSON (как массив позиций)
        std::cout << "{";
        for (size_t i = 0; i < positions.size(); ++i) {
            std::cout << positions[i];
            if (i != positions.size() - 1)
                std::cout << ", ";
        }
        std::cout << "}" << std::endl;
    }
    
    return 0;
}
