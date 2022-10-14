#ifndef HOSTS_HPP
#define HOSTS_HPP
#pragma once

#include <curl/curl.h>
#include <string>
#include <utility> // std::pair
#include <set>
#include <iterator>
#include "defines.hpp"

typedef std::set<std::pair<std::string, std::string> > host_set;

// extern struct curl_slist *g_curl_host_list;
// extern host_set g_host_set;


// curl_slist *create_host_list(void);
void add_hosts(void);
void add_host(const std::string& server_name, const std::string& port);

#endif