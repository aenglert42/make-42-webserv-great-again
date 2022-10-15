#ifndef CLIENT_HPP
#define CLIENT_HPP
#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <iostream>

#include "defines.hpp"
#include "utils.hpp"

#define UNKNOWN -2
#define BUFFER_SIZE 1024

extern uint16_t g_port_for_custom_requests;

void custom_request(const std::string&, const std::string&, const std::string&);

#endif