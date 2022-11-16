#include	"../includes/Server.hpp"

/*---------------Constructor/Destructor--------------*/

Server::Server(const std::string& port, const std::string& password)
:_port(port), _password(password){}

Server::~Server(){}

/*---------------------Accessors--------------------*/

int		Server::getServerFd(void)
{
	return (_serverFd);
}

int		Server::getSocketOpt(void)
{
	return (_socketOpt);
}

/*-----------------MemberFunctions------------------*/

void	Server::start(void)
{
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw	std::runtime_error("socket failed");
}