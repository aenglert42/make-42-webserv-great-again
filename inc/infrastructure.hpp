#ifndef INFRASTRUCTURE_HPP
#define INFRASTRUCTURE_HPP
#pragma once

#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>

// directories
#define ROOT "./server/root/"
#define DIR ROOT"dir/"
#define ONE DIR"one/"
#define TWO ONE"two/"
#define PERMISSION_DIR DIR"permission_dir/"
#define NO_PERMISSION_DIR DIR"no_permission_dir/"
#define UPLOADS DIR"uploads/"
#define INDEX DIR"index/"
#define CUSTOM_INDEX INDEX"custom/"
#define AUTOINDEX INDEX"no/autoindex/"
#define NO_AUTOINDEX INDEX"no/no_autoindex/"
#define AUTOINDEX_NO_PERMISSION_DIR AUTOINDEX"no_permission_dir/"
#define NO_DELETE_DIR UPLOADS"no_permission_dir/"

#define SERVER1 ROOT"server1/"
#define SERVER1_CUSTOM SERVER1"custom/"

#define SERVER2 ROOT"server2/"

// files
#define FILE "file"
#define NO_PERMISSION_FILE "no_permission_file"
#define NO_PERMISSION_FILE_CGI "no_permission_file.cgi"
#define DOT_CGI ".cgi"
#define CGI_FILE "file.cgi"
#define INDEX_HTML "index.html"
#define CUSTOM_HTML "custom.html"

void create_infrastructure(void);

void clear_infrastructure(void);

#endif