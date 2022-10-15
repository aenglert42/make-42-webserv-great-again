#ifndef DELETE_HPP
#define DELETE_HPP
#pragma once

#include <string>
#include "defines.hpp"
#include "curl_requests.hpp"

#define DELETE_REQUEST(REQUEST, RESPONSE) DELETE_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_DELETE_tests(void);

#endif