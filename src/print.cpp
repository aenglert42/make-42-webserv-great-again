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

void print_section_title(void)
{
	std::cout << GREEN << BOLD << "Custom Requests" << RESET<< std::endl;
}

void print_section_title(const std::string& section)
{
	std::cout << GREEN << BOLD << section << " Requests" << RESET<< std::endl;
}

void print_test_title(int i, const std::string& section, const std::string& testCase, const std::string& testLocation)
{
	std::cout << YELLOW << "Test " << i << ": " << section << " " << testCase << RESET << " located in: " << BLUE << testLocation << RESET << std::endl;
}

void print_test_title(int i, const std::string& testCase, const std::string& testLocation)
{
	std::cout << YELLOW << "Test " << i << ": " << testCase << RESET << " located in: " << BLUE << testLocation << RESET << std::endl;
}

void print_summary(void)
{
	std::cout << GREEN << BOLD << std::endl << "Done." << RESET << std::endl;
	if (g_ko_counter > 0)
		std::cout << RED << BOLD << g_ko_counter << " tests failed!" << RESET << std::endl;
}