#ifndef UTILS_HPP
#define UTILS_HPP
#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include "defines.hpp"

#define INVALID -1

extern int g_ko_counter;

void evaluate_test(const std::string&, const std::string&, const std::string&, long, const std::string&);

#endif