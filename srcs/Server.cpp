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
	bzero((void *)_buffer, BUFF_SIZE);
	_password = password;
	_commandMap["NICK"] = &Server::nick;
	_commandMap["PASS"] = &Server::pass;
	_commandMap["CAP"] = &Server::cap;
	_commandMap["USER"] = &Server::user;
	_commandMap["JOIN"] = &Server::join;
	_commandMap["QUIT"] = &Server::quit;
	_commandMap["PING"] = &Server::ping;
	_commandMap["PRIVMSG"] = &Server::privMsg;
	_commandMap["NOTICE"] = &Server::notice;
	_commandMap["KICK"] = &Server::kick;
	// _commandMap["MODE"] = &Server::mode;
}

Server::~Server(){}

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
	std::cout << "\rIncoming connection..." << std::endl;
	FD_SET(newClient, &_clientFds);
}

void	Server::connectionLost(int currentFd)
{
	std::cout << "\rConnection lost with " << _clientMap[currentFd].getNickname() << std::endl;
	FD_CLR(currentFd, &_clientFds);
	FD_CLR(currentFd, &_readFds);
	FD_CLR(currentFd, &_writeFds);
	std::map<int, Client>::iterator it = _clientMap.find(currentFd);
	_clientMap.erase(it);
}

void	Server::handleMsg(int currentFd)
{
	char	buffer[BUFF_SIZE];
	bzero(buffer, BUFF_SIZE);
	_commandRecv.clear();
	if (recv(currentFd, (void *)buffer, BUFF_SIZE, 0) < 0)
		connectionLost(currentFd);
	if (!buffer[0])
	{
		bzero(buffer, BUFF_SIZE);
		FD_CLR(currentFd, &_clientFds);
	}
	_clientMap[currentFd].appendBuff += buffer;
	size_t	pos = 0;
	std::string temp = _clientMap[currentFd].appendBuff;
	while ((pos = temp.find("\r\n")) != std::string::npos)
	{
		_commandRecv.push_back(temp.substr(0, pos));
		temp = temp.substr(pos + 2, temp.size());
	}
	_clientMap[currentFd].appendBuff.clear();
	_clientMap[currentFd].appendBuff = temp;
	for (std::vector<std::string>::iterator it = _commandRecv.begin(); it != _commandRecv.end(); it++)
	{
		_clientMap[currentFd].tokenize(*it);
		execCommand(_clientMap[currentFd]);
		_clientMap[currentFd].clearTokens();
		if (_clientMap[currentFd].getReply().size() && _clientMap[currentFd].getAuth())
			FD_SET(currentFd, &_writeFds);
		if (_clientMap[currentFd].getAuth() == -1)
				FD_CLR(currentFd, &_clientFds);
		_clientMap[currentFd].clearTokens();
	}
	temp.clear();
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
				send(currentFd, _clientMap[currentFd].getReply().c_str(), _clientMap[currentFd].getReply().size(), 0);
				_clientMap[currentFd].clearReply();
				FD_CLR(currentFd, &_writeFds);
			}	
		}
	}
}