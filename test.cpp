#include <iostream>
#include <fstream>
#include <mutex>
#include <string>

class Logger {
public:
    enum Level { INFO, WARNING, ERROR };

    Logger(const std::string& filename) : file(filename, std::ios_base::app) {}

    void log(Level level, const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        if (file.is_open()) {
            file << levelToString(level) << ": " << message << std::endl;
        }
    }

private:
    std::ofstream file;
    std::mutex mtx;

    std::string levelToString(Level level) {
        switch (level) {
            case INFO: return "INFO";
            case WARNING: return "WARNING";
            case ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }
};
int main() {
    Logger logger("log.txt");
    logger.log(Logger::INFO, "Program started");
    logger.log(Logger::ERROR, "An error occurred");
    return 0;
}