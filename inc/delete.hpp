#ifndef DELETE_HPP
#define DELETE_HPP
#pragma once

#include <string>
#include "defines.hpp"
#include "curl_requests.hpp"

#define DELETE_TEST(REQUEST, RESPONSE) DELETE_test(#REQUEST, #RESPONSE, FILE_LINE)

void run_DELETE_tests(void);

#endif