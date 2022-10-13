#ifndef CUSTOM_HPP
#define CUSTOM_HPP
#pragma once

// #include <iostream> //std::ostream
// #include <list>
#include <string>
#include "defines.hpp"

void run_custom_tests(void);
void custom_request(const std::string& url, const std::string& expected, const std::string &testLocation);

// std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif