#pragma		once

#include	"../includes/Utils.hpp"

class Client
{
private:
	int						_clientFd;
	struct sockaddr_in		_clientAddr;
	std::string				_nickname;

public:
	Client(void);
	~Client();

	void	setFd(int _clientFd);
	void	setAdress(struct sockaddr_in clientAddr);
	void	setNickname(std::string nickname);

	const std::string	getNickname(void);
};
