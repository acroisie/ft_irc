#pragma		once

#include	"../includes/Utils.hpp"
#include	"../includes/Client.hpp"


class Client;
class Commands;

class Server
{
private:
	std::string					_port;
	std::string					_password;
	int							_serverFd;
	int							_opt;
	struct fd_set				_clientFds;
	struct fd_set				_readFds;
	struct fd_set				_writeFds;
	struct sockaddr_in			_address;
	int							_addrLen;
	struct timeval				_timeout;
	std::map<int, Client>		_clientMap;
	std::map<int, void *>		_serverMap;
	std::map<std::string, void (Server::*)(Client &)>	_commandMap;
	

	std::string					_appendBuff;
	char						_buffer[BUFF_SIZE];

public:
	Server(const std::string& port, const std::string& password);
	~Server();

	char*	getBuffer(void);

	void	start(void);
	void	socketInit(void);
	void	acceptNewClient(void);
	void	handleMsg(int currentFd);

	void		execCommand(Client &client);

	void		nick(Client &client);
	void		pass(Client &client);
	void		user(Client &client);
	void		cap(Client &client);
	void		join(Client &client);
	void		quit(Client &client);
};