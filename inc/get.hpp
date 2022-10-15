#ifndef GET_HPP
#define GET_HPP
#pragma once

#include <string>
#include "defines.hpp"
#include "curl_requests.hpp"

#define GET_REQUEST(REQUEST, RESPONSE) GET_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_GET_tests(void);

#endif