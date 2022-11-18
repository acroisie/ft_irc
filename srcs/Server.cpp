#include	"../includes/Server.hpp"

/*---------------Constructor/Destructor--------------*/

Server::Server(const std::string& port, const std::string& password)
:_port(port), _password(password)
{
	_opt = 1;
	_timeout.tv_sec = 3 * 60;
	_timeout.tv_usec = 0;
}

Server::~Server(){}

/*---------------------Accessors--------------------*/

int		Server::getServerFd(void)
{
	return (_serverFd);
}

/*-----------------MemberFunctions------------------*/

void	Server::start(void)
{
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw	std::runtime_error("socket failed");
	if ((setsockopt(_serverFd, SOL_SOCKET,SO_REUSEADDR, &_opt, sizeof(_opt))) < 0)
		throw	std::runtime_error("setsocketopt failed");
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(atoi(_port.c_str()));
	if (bind(_serverFd, (struct sockaddr*)&_address, (socklen_t)sizeof(_address)) < 0)
		throw	std::runtime_error("bind failed");
	if (listen(_serverFd, 42) < 0)
		throw	std::runtime_error("listen failed");
	FD_ZERO(&_readFds);
	FD_ZERO(&_writeFds);
	FD_SET(_serverFd, &_readFds);
	FD_SET(_serverFd, &_writeFds);
	int select_rvalue;
	char buffer[500];
	bzero((void *)buffer, sizeof(buffer));
	while (true)
	{
		std::cout << "Listen..." << std::endl;
		if (((select_rvalue = select(43, &_readFds, &_writeFds, NULL, &_timeout))) <= 0)
			throw std::runtime_error("timeout");
		for (int i = 0; i <= 43 ; i++)
		{
			if (FD_ISSET(i, &_readFds))
			{
				if (i == _serverFd)
				{
					int addrlen = sizeof(_address);
					if ((_newSocket = accept(_serverFd, (struct sockaddr*)&_address, (socklen_t*)&addrlen)) < 0)
						throw	std::runtime_error("accept failed");
					std::cout << "connected" << std::endl;
					FD_SET(_newSocket, &_readFds);
					std::stringstream buff;
					buff << _newSocket;
					std::string welcome = "001 " + buff.str() + " :Welcome to the 127.0.0.1 Network, acroisie\r\n";

					if (send(_newSocket, welcome.c_str(), welcome.size(), 0) < 0)
						throw std::runtime_error("send failed");
				}
				else
				{
					if (recv(i, (void*)buffer, sizeof(buffer), 0) <= 0)
						throw std::runtime_error("recv failed");
					std::cout << buffer;	
				}
			}
		}
		
	}
}