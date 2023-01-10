#include	"../includes/Server.hpp"
using		namespace std;

/*---------------Constructor/Destructor--------------*/

Server::Server(const string& port, const string& password)
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
	_commandMap["MODE"] = &Server::mode;
	_commandMap["TOPIC"] = &Server::topic;
	_commandMap["KICK"] = &Server::kick;
	_commandMap["PART"] = &Server::part;
	_commandMap["INVITE"] = &Server::invite;
}

Server::~Server()
{
	for (map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
		close(it->first);
	close(_serverFd);
	cout << "\rServer down." << endl;
}

/*-----------------MemberFunctions------------------*/

int	Server::segvGuard(Client &client)
{
	if (client.getTokens().size() < 2)
	{
		client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[0]));
		return (1);
	}
	return (0);
}

void	Server::acceptNewClient(void)
{
	int						newClient;
	struct sockaddr_in		clientAddr;
	socklen_t				addrLen;
	addrLen = sizeof(clientAddr);
	if ((newClient = accept(_serverFd, (struct sockaddr*)&clientAddr, (socklen_t*)&addrLen)) < 0)
		throw	runtime_error("accept failed");
	_clientMap[newClient].addClientFd(newClient);
	_clientMap[newClient].setAdress(clientAddr);
	_clientMap[newClient].addClientFd(newClient);
	cout << "\rIncoming connection..." << endl;
	FD_SET(newClient, &_clientFds);
}

void	Server::handleMsg(int currentFd)
{
	char	buffer[BUFF_SIZE];
	bzero(buffer, BUFF_SIZE);
	_commandRecv.clear();
	if (recv(currentFd, (void *)buffer, BUFF_SIZE - 1, 0) < 0)
		quit(_clientMap[currentFd]);
	if (!buffer[0])
	{
		bzero(buffer, BUFF_SIZE);
		FD_CLR(currentFd, &_clientFds);
		return;
	}
	_clientMap[currentFd].appendBuff += buffer;
	size_t	pos = 0;
	string temp = _clientMap[currentFd].appendBuff;
	while ((pos = temp.find("\r\n")) != string::npos)
	{
		_commandRecv.push_back(temp.substr(0, pos));
		temp = temp.substr(pos + 2, temp.size());
	}
	_clientMap[currentFd].appendBuff.clear();
	_clientMap[currentFd].appendBuff = temp;
	for (vector<string>::iterator it = _commandRecv.begin(); it != _commandRecv.end(); it++)
	{
		_clientMap[currentFd].tokenize(*it);
		if(_clientMap[currentFd].getTokens().empty())
			return;
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
		throw	runtime_error("socket creation failed");
	if (fcntl(_serverFd, F_SETFL, O_NONBLOCK) < 0)
		throw	runtime_error("fcntl failed");
	if ((setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt))) < 0)
		throw	runtime_error("reuse of socket failed");
	if (bind(_serverFd, (struct sockaddr*)&_address, (socklen_t)sizeof(_address)) < 0)
		throw	runtime_error("bind failed");
	if (listen(_serverFd, MAX_CONNECTIONS) < 0)
		throw	runtime_error("listen failed");
	FD_SET(_serverFd, &_clientFds);
}

bool Server::running = true;

void	Server::start()
{
	socketInit();
	while (running)
	{
		_readFds = _clientFds;
		cout << "\rListen..." << flush;
		if (!(select(MAX_CONNECTIONS + 1, &_readFds, &_writeFds, NULL, &_timeout)))
		{
			cout << "\rTime-out" << endl;
			running = false;
		}
		if (!running)
			break;
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