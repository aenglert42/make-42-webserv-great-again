#ifndef CURL_REQUESTS_HPP
#define CURL_REQUESTS_HPP
#pragma once

#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <curl/curl.h>
#include "utils.hpp"
#include "print.hpp"

typedef std::set<std::pair<std::string, std::string> > host_set;

extern int g_ko_counter;
extern curl_slist *g_curl_host_list;
extern host_set g_host_set;


void GET_test(const std::string&, const std::string&, const std::string&);

void POST_test(const std::string&, const std::string&, const std::string&);

void DELETE_test(const std::string&, const std::string&, const std::string&);

void create_curl_host_list(void);

void add_host(const std::string&, const std::string&);

#endif