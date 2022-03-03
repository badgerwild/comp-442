//
// Created by jason on 2/25/22.
//

#include "logSubject.h"
#include "messageBuilder.h"

Logger::Logger() = default;
Logger::~Logger() = default;

void Logger::log(messageBuilder M) {
    notify(*this, M);
}