//
// Created by jason on 2/25/22.
//

#include "logSubject.h"

Logger::Logger() = default;
Logger::~Logger() = default;

void Logger::log(std::string s, bool valid) {
    notify(*this, s, valid);
}