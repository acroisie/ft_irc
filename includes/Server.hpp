#pragma		once

#include	"../includes/Utils.hpp"
#include	"../includes/Client.hpp"
#include	"../includes/Commands.hpp"

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
	char						_buffer[BUFF_SIZE];
	Commands					_command;

public:
	Server(const std::string& port, const std::string& password);
	~Server();

	const std::string	getBuffer(void);

	void	start(void);
	void	socketInit(void);
	void	acceptNewClient(void);
	void	handleMsg(int currentFd);
};