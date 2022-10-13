#ifndef HOSTS_HPP
#define HOSTS_HPP
#pragma once

#include <curl/curl.h>
#include <string>
#include <utility> // std::pair
#include <set>
#include <iterator>
#include "defines.hpp"

static struct curl_slist *host = NULL;

typedef std::set<std::pair<std::string, std::string> > host_set;

curl_slist *create_host_list(void);

#endif