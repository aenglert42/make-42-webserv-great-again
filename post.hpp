#ifndef POST_HPP
#define POST_HPP
#pragma once

// #include <iostream> //std::ostream
// #include <list>
#include <string>
#include "defines.hpp"

#define POST_REQUEST(REQUEST, RESPONSE) POST_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_POST_tests(void);
void POST_request(const std::string& url, const std::string& expected, const std::string &testLocation);

// std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif