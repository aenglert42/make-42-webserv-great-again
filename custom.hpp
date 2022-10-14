#ifndef CUSTOM_HPP
#define CUSTOM_HPP
#pragma once

// #include <iostream> //std::ostream
// #include <list>
#include <string>
#include "defines.hpp"

extern uint16_t g_port_for_custom_requests;
// #define PORT 8080

#define CUSTOM_REQUEST(REQUEST, RESPONSE) custom_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_custom_tests(void);
void custom_request(const std::string& request, const std::string& expected, const std::string &testLocation);

// std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif