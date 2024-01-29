#include "log.hpp"

void rlog::info(const std::string &api, const std::string &in) {
    std::cout << "[\033[38;5;243m" << api << "/api\033[0m]: " << in <<
        std::endl;
}

void rlog::error(const std::string &api, const std::string &in) {
    std::cout << "[\033[38;5;160mERROR\033[0m \033[38;5;243m" << api
        << "/api\033[0m]: " << in << std::endl;
}

void rlog::warning(const std::string &api, const std::string &in) {
    std::cout << "[\033[38;5;208mWARNING\033[0m \033[38;5;243m" << api
        << "/api\033[0m]: " << in << std::endl;
}

void rlog::info(const std::string &info) {
    std::cout << "[INFO]: " << info << std::endl;
}

void rlog::warning(const std::string &in) {
    std::cout << "[\033[38;5;208mWARNING\033[0m]: " << in << std::endl;
}

void rlog::error(const std::string &in) {
    std::cout << "[\033[38;5;160mERROR\033[0m]: " << in << std::endl;
}
