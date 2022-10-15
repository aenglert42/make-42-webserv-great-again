#ifndef POST_HPP
#define POST_HPP
#pragma once

#include <string>
#include "defines.hpp"
#include "curl_requests.hpp"

#define POST_REQUEST(REQUEST, RESPONSE) POST_request(#REQUEST, #RESPONSE, FILE_LINE)

void run_POST_tests(void);

#endif