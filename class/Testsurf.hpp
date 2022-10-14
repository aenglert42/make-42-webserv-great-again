#ifndef TESTSURF_HPP
#define TESTSURF_HPP
#pragma once

#include <iostream> //std::ostream
#include <list>

class Testsurf
{
	private:
		Testsurf(const Testsurf&);
		Testsurf& operator=(const Testsurf&);
		std::string status;
		std::list<std::pair<std::string, std::string> > hosts;
	public:
		Testsurf(void);
		~Testsurf(void);
		void setStatus(const std::string&);
		const std::string& getStatus(void) const;

	// class BadRequestException : public std::exception
	// {
	// 	public:
	// 		virtual const char* what() const throw();
	// };
};

std::ostream& operator<<(std::ostream&, const Testsurf&);

#endif