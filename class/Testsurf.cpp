#include "Testsurf.hpp"

Testsurf::Testsurf(void)
{

}

Testsurf::~Testsurf(void)
{

}

void Testsurf::setStatus(const std::string& status)
{
	// if (!isValidStatus(status))
	// 	throw InvalidStatus();
	// this->status = status;
	// this->statusMessage = this->messageMap[this->status];
}

const std::string& Testsurf::getStatus(void) const
{
	return (this->status);
}

std::ostream& operator<<(std::ostream& out, const Testsurf& response)
{
	// out << response.getProtocol() << " "
	// << response.getStatus() << " "
	// << response.getStatusMessage() << std::endl;
	// for (std::map<std::string, std::string>::const_iterator it = response.getHeaderFields().begin(); it != response.getHeaderFields().end(); ++it)
	// {
	// 	out << it->first << ": "
	// 	<< it->second << "\n";
	// }
	// out << response.getBody() << std::endl;
	return (out);
}

// const char* Testsurf::BadRequestException::what(void) const throw()
// {
// 	return ("400");
// }