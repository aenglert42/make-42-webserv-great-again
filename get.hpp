#ifndef GET_HPP
#define GET_HPP
#pragma once

// #include <iostream> //std::ostream
// #include <list>
#include <string>
#include "defines.hpp"

void run_GET_tests(void);
void GET_request(const std::string& url, const std::string& expected, const std::string &testLocation);

// std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif