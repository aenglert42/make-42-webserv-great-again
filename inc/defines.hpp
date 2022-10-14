#ifndef DEFINES_HPP
#define DEFINES_HPP
#pragma once

// Colors and Printing
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define UNDERLINED "\033[4m"
#define FILE_LINE (std::string(__FILE__) + std::string(":") + std::to_string(__LINE__))

#define LOG(x) (std::cout << __FILE__ << ":" << __LINE__ << " " << x << std::endl)

#endif