#ifndef PRINT_HPP
#define PRINT_HPP
#pragma once

#include <string>
#include <iostream>
#include "defines.hpp"

#define GET "GET"
#define POST "POST"
#define DELETE "DELETE"

extern int g_ko_counter;

void print_welcome(void);

void print_section_title(void);

void print_section_title(const std::string& section);

void print_test_title(int i, const std::string& section, const std::string& testCase, const std::string& testLocation);

void print_test_title(int i, const std::string& testCase, const std::string& testLocation);

void print_summary(void);

#endif