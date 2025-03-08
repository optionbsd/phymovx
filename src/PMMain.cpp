#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Simulation.h"

// Функция для преобразования строки с суффиксом "s" в секунды (например, "1s")
double parseDuration(const std::string& durationStr) {
    std::istringstream iss(durationStr);
    double value;
    iss >> value;
    return value; // предполагаем, что суффикс "s" просто опускается
}

// Простейший парсер командной строки
struct CmdOptions {
    int steps = 0;
    double duration = 0.0;
    double startpos = 0.0;
    double endpos = 0.0;
    double gravity = 0.0;
};

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
        }
    }
    return opts;
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
        options.gravity
    );
    
    // Выводим результат в формате {v1, v2, ...}
    std::cout << "{";
    for (size_t i = 0; i < positions.size(); ++i) {
        std::cout << positions[i];
        if (i != positions.size() - 1)
            std::cout << ", ";
    }
    std::cout << "}" << std::endl;
    
    return 0;
}
