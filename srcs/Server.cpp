#include	"../includes/Server.hpp"

/*---------------Constructor/Destructor--------------*/

Server::Server(const std::string& port, const std::string& password)
:_port(port)
{
	FD_ZERO(&_clientFds);
	FD_ZERO(&_writeFds);
	_opt = 1;
    _address.sin_family = AF_INET;
    _address.sin_addr.s_addr = INADDR_ANY;
    _address.sin_port = htons(atoi(_port.c_str()));
	_addrLen = sizeof(_address);
	_timeout.tv_sec = 3 * 60;
	_timeout.tv_usec = 0;
	_command.setPassword(password);
	bzero((void *)_buffer, BUFF_SIZE);
}

Server::~Server(){}

/*----------------------Getters---------------------*/

char*	Server::getBuffer(void){return (_buffer);}

/*-----------------MemberFunctions------------------*/

void	Server::acceptNewClient(void)
{
	int						newClient;
	struct sockaddr_in		clientAddr;
	socklen_t				addrLen;
	addrLen = sizeof(clientAddr);
	if ((newClient = accept(_serverFd, (struct sockaddr*)&clientAddr, (socklen_t*)&addrLen)) < 0)
		throw	std::runtime_error("accept failed");
	_clientMap[newClient].setFd(newClient);
	_clientMap[newClient].setAdress(clientAddr);
	_clientMap[newClient].setFd(newClient);
	std::cout << "\rconnected" << std::endl;
	FD_SET(newClient, &_clientFds);
}

void	Server::handleMsg(int currentFd)
{
	if (recv(currentFd, (void*)_buffer, BUFF_SIZE, 0) <= 0)
		throw std::runtime_error("recv failed");
	_command.tokenize(_buffer);
	_command.execCommand(_clientMap[currentFd]);	
	bzero(_buffer, strlen(_buffer));
	_command.clearTokens();
	if (_command.getReply().size())
		FD_SET(currentFd, &_writeFds);
	if (_clientMap[currentFd].getAuth() == -1)
		FD_CLR(currentFd, &_clientFds);
}

void	Server::socketInit(void)
{
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw	std::runtime_error("socket creation failed");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) < 0)
		throw	std::runtime_error("fcntl failed");
	if ((setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) < 0)
		throw	std::runtime_error("reuse of socket failed");
	if (bind(_serverFd, (struct sockaddr*)&_address, (socklen_t)sizeof(_address)) < 0)
		throw	std::runtime_error("bind failed");
	if (listen(_serverFd, MAX_CONNECTIONS) < 0)
		throw	std::runtime_error("listen failed");
	FD_SET(_serverFd, &_clientFds);
}

void	Server::start()
{
	socketInit();
	while (true)
	{
		_readFds = _clientFds;
		std::cout << "\rListen..." << std::flush;
		if (!(select(MAX_CONNECTIONS + 1, &_readFds, &_writeFds, NULL, &_timeout)))
			throw std::runtime_error("time-out");
		for (int currentFd = 0; currentFd <= (MAX_CONNECTIONS + 1) ; currentFd++)
		{
			if (FD_ISSET(currentFd, &_readFds))
			{
				if (currentFd == _serverFd)
					acceptNewClient();
				else
					handleMsg(currentFd);
			}
			else if (FD_ISSET(currentFd, &_writeFds))
			{
				send(currentFd, _command.getReply().c_str(), _command.getReply().size(), 0);
				FD_CLR(currentFd, &_writeFds);
			}	
		}
	}
}