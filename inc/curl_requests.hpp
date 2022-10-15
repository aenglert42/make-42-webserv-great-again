#ifndef CURL_REQUESTS_HPP
#define CURL_REQUESTS_HPP
#pragma once

#include <iostream>
#include <string>
#include <iterator>
#include <set>
#include <curl/curl.h>
#include "utils.hpp"

typedef std::set<std::pair<std::string, std::string> > host_set;

extern int g_ko_counter;
extern curl_slist *g_curl_host_list;
extern host_set g_host_set;


void GET_request(const std::string&, const std::string&, const std::string&);

void POST_request(const std::string&, const std::string&, const std::string&);

void DELETE_request(const std::string&, const std::string&, const std::string&);

void add_hosts_to_curl(void);

void add_host(const std::string&, const std::string&);

#endif