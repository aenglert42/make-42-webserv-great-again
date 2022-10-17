#ifndef HOSTS_HPP
#define HOSTS_HPP
#pragma once

#include <curl/curl.h>
#include <string>
#include <utility> // std::pair
#include <set>
#include "defines.hpp"

void add_hosts(void);

void add_host(const std::string&, const std::string&);

#endif