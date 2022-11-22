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

void	Server::socketInit(void)
{
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw	std::runtime_error("socket failed");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) < 0)
		throw	std::runtime_error("fcntl failed");
	FD_ZERO(&_clientFds);
	FD_ZERO(&_writeFds);
	FD_SET(_serverFd, &_clientFds);
	FD_SET(_serverFd, &_writeFds);
	if ((setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) < 0)
		throw	std::runtime_error("reuse of socket failed");
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(atoi(_port.c_str()));
	if (bind(_serverFd, (struct sockaddr*)&_address, (socklen_t)sizeof(_address)) < 0)
		throw	std::runtime_error("bind failed");
	if (listen(_serverFd, MAX_CONNECTIONS) < 0)
		throw	std::runtime_error("listen failed");
	bzero((void *)_buffer, sizeof(_buffer));
}

void	Server::handleMessage(int	currentFd)
{
	if (recv(currentFd, (void*)_buffer, sizeof(_buffer), 0) <= 0)
		throw std::runtime_error("recv failed");
	std::cout << "\r\n[" << _buffer << "]\n";
	FD_SET(currentFd,&_writeFds);
}
void	Server::start(void)
{
	socketInit();
	while (true)
	{
		_readFds = _clientFds;
		std::cout << "Listen..." << std::flush;
		if ((select(MAX_CONNECTIONS + 1, &_readFds, &_writeFds, NULL, &_timeout)) <= 0)
			throw std::runtime_error("timeout");
		for (int currentFd = 0; currentFd <= (MAX_CONNECTIONS + 1) ; currentFd++)
		{
			if (FD_ISSET(currentFd, &_readFds))
			{
				if (currentFd == _serverFd)
				{
					int addrlen = sizeof(_address);
					if ((_newSocket = accept(_serverFd, (struct sockaddr*)&_address, (socklen_t*)&addrlen)) < 0)
						throw	std::runtime_error("accept failed");
					std::cout << "connected" << std::endl;
					FD_SET(_newSocket, &_clientFds);
					//handleConnexion()
					// std::stringstream buff;
					// buff << _newSocket;
					// std::string welcome = "001 " + buff.str() + " :Welcome to thejdfg dsdgsjkdfgjkdfg.1 Network\r\n";
					// if (send(_newSocket, welcome.c_str(), welcome.size(), 0) < 0)
					// 	throw std::runtime_error("send failed");
				}
				else
					handleMessage(currentFd);
			}
			else if (FD_ISSET(currentFd, &_writeFds))
			{
				if(send(currentFd, "test",4, 0) < 0)
					throw std::runtime_error("send fail");
				FD_CLR(currentFd,&_writeFds);
			}
		}
		
	}
}