#pragma		once
#include	<iostream>
// #include	<stdexcept>

class Server
{
private:
	const std::string	_port;
	const std::string	_password;
public:
	Server(const std::string& port, const std::string& password);
	~Server();
};
