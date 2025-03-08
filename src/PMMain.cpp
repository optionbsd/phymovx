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
    return value;
}

// Простейший парсер аргументов командной строки
struct CmdOptions {
    int steps = 0;
    double duration = 0.0;
    double startpos = 0.0;
    double endpos = 0.0;
    double gravity = 0.0;
    double friction = 0.0;
    bool collision = false;
    double restitution = 1.0;
    std::string outputType = "json"; // "json" или "css"
    std::string assetPath = "";      // путь к XML-ассету (если задан)
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
        } else if (arg == "-friction" && i+1 < argc) {
            opts.friction = std::stod(argv[++i]);
        } else if (arg == "-collision" && i+1 < argc) {
            std::string col = argv[++i];
            opts.collision = (col == "true" || col == "1");
        } else if (arg == "-restitution" && i+1 < argc) {
            opts.restitution = std::stod(argv[++i]);
        } else if (arg == "-output" && i+1 < argc) {
            opts.outputType = argv[++i];
        } else if (arg == "-asset" && i+1 < argc) {
            opts.assetPath = argv[++i];
        }
    }
    return opts;
}

int main(int argc, char* argv[]) {
    CmdOptions options = parseArguments(argc, argv);
    if (options.steps <= 0 || options.duration <= 0.0) {
        std::cerr << "Необходимо указать корректное число шагов и длительность." << std::endl;
        return 1;
    }

    std::vector<double> positions;

    // Если указан ассет, загружаем XML и генерируем последовательность на его основе
    if (!options.assetPath.empty()) {
        std::vector<double> assetKeyframes = loadAsset(options.assetPath);
        if (assetKeyframes.empty()) {
            std::cerr << "Ошибка загрузки ассета или в ассете отсутствуют ключевые кадры." << std::endl;
            return 1;
        }
        positions = runAssetSimulation(assetKeyframes, options.steps);
    }
    // Иначе используем физическую симуляцию (с учетом гравитации, трения и столкновений)
    else {
        positions = runSimulation(options.steps, options.duration, options.startpos, options.endpos,
                                  options.gravity, options.friction, options.collision, options.restitution);
    }

    // Вывод в зависимости от выбранного формата
    if (options.outputType == "css") {
        std::cout << generateCssAnimation(positions, options.duration, options.steps) << std::endl;
    } else {
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
