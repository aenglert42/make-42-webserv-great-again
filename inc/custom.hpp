#ifndef CUSTOM_HPP
#define CUSTOM_HPP
#pragma once

#include <string>
#include "defines.hpp"
#include "client.hpp"

#define CUSTOM_REQUEST(REQUEST, RESPONSE) custom_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_custom_tests(void);

#endif