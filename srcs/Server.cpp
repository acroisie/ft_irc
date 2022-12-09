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
	// _commandMap["PING"] = &Server::ping;
	_commandMap["PRIVMSG"] = &Server::privMsg;
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
	std::cout << clientAddr.sin_addr.s_addr << std::endl;
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
	_commandRecv.clear(); // clear le vecteur de commande
	if (recv(currentFd, buffer, BUFF_SIZE, 0) < 0)
		connectionLost(currentFd);
	if (!buffer[0])
	{
		FD_CLR(currentFd, &_clientFds); //clear le client set au cas ou le buff est vide ( a voir pour le gerer dans le auth ce que je te disais)
		return;
	}
	std::cout << "buffer : [" << buffer << "] \n";
	_clientMap[currentFd].appendBuff += buffer;
	size_t	pos = 0;
	std::string temp = _clientMap[currentFd].appendBuff;
	while ((pos = temp.find("\r\n")) != std::string::npos)
	{
		_commandRecv.push_back(temp.substr(0, pos)); // stocker toutes les commandes recu dans un vecteur
		std::cout << "temp :  [" << temp.substr(0, pos) <<"]\n";

		// il faut supprimer la premiere command trouvé (NICK lnemor\r\n)
		// ducoup je substr de la fin de la premiere trouver jusqu'au bout
		temp = temp.substr(pos + 2, temp.size());
	}
	std::cout << "temp2 : (" << temp << ")\n";
	_clientMap[currentFd].appendBuff = temp;// sauvegarde la derniere partie de temp
	for (std::vector<std::string>::iterator it = _commandRecv.begin(); it != _commandRecv.end(); it++) // exec toutes les commandes dans le vecteur
	{
		//std::cout << " ( "<< *it << " )\n";
		_clientMap[currentFd].tokenize(*it);
		execCommand(_clientMap[currentFd]);
		_clientMap[currentFd].clearTokens();
		if (_clientMap[currentFd].getReply().size() && _clientMap[currentFd].getAuth())
			FD_SET(currentFd, &_writeFds);
		if (_clientMap[currentFd].getAuth() == -1)
			FD_CLR(currentFd, &_clientFds);
		_clientMap[currentFd].clearTokens();
	}
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