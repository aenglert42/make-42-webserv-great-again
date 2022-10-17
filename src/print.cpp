#include "print.hpp"

void print_welcome(void)
{
	std::cout << GREEN << BOLD << "\
   __            __                  ____\n\
  / /____  _____/ /________  _______/ __/\n\
 / __/ _ \\/ ___/ __/ ___/ / / / ___/ /_\n\
/ /_/  __(__  ) /_(__  ) /_/ / /  / __/\n\
\\__/\\___/____/\\__/____/\\__,_/_/  /_/\n\
" << RESET<< std::endl;
}

void print_custom(void)
{
	std::cout << GREEN << BOLD << "Custom Requests" << RESET<< std::endl;
}

void print_GET(void)
{
	std::cout << GREEN << BOLD << "GET Requests" << RESET<< std::endl;
}

void print_POST(void)
{
	std::cout << GREEN << BOLD << "POST Requests" << RESET<< std::endl;
}

void print_DELETE(void)
{
	std::cout << GREEN << BOLD << "DELETE Requests" << RESET<< std::endl;
}

void print_summary(void)
{
	std::cout << GREEN << BOLD << std::endl << "Done." << RESET << std::endl;
	if (g_ko_counter > 0)
		std::cout << RED << BOLD << g_ko_counter << " tests failed!" << RESET << std::endl;
}