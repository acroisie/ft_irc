#pragma		once

#include	"../includes/Utils.hpp"

class Client
{
private:
	int						_clientFd;
	struct sockaddr_in		_clientAddr;

public:
	Client(void);
	~Client();

	void	setFd(int _clientFd);
	void	setAdress(struct sockaddr_in clientAddr);
};
