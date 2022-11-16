#pragma		once
#include	<iostream>
#include	<sys/socket.h>

class Server
{
private:
	const std::string	_port;
	const std::string	_password;
	int					_serverFd;
	int					_socketOpt;
public:
	Server(const std::string& port, const std::string& password);
	~Server();

	int		getServerFd(void);
	int		getSocketOpt(void);
	void	start(void);
};
