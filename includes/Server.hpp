#pragma		once

#include	<iostream>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<errno.h>

class Server
{
private:
	const std::string	_port;
	const std::string	_password;
	struct sockaddr_in	_address;
	int					_serverFd;
	int					_newSocket;
public:
	Server(const std::string& port, const std::string& password);
	~Server();

	int		getServerFd(void);
	int		getSocketOpt(void);
	void	start(void);
};
