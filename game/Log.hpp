#pragma once

#include "Vision.hpp"

#ifndef LOG_PATH
#define LOG_PATH "../data/log.txt"
#endif

void startFile(int amount, int inputs, int outputs, bool clear = false);

std::string join(const FloatVector& vector);

void logFile(const FloatVector& input, const FloatVector& output, bool clear = false);