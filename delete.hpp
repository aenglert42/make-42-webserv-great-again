#ifndef DELETE_HPP
#define DELETE_HPP
#pragma once

// #include <iostream> //std::ostream
// #include <list>
#include <string>
#include "defines.hpp"

#define DELETE_REQUEST(REQUEST, RESPONSE) DELETE_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_DELETE_tests(void);
void DELETE_request(const std::string& url, const std::string& expected, const std::string &testLocation);

// std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif