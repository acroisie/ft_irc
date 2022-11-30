#pragma		once

#include	"../includes/Utils.hpp"

class Client
{
private:
	int						_clientFd;
	struct sockaddr_in		_clientAddr;
	std::string				_nickname;
	int						_isAuth;

public:
	Client(void);
	~Client();

	void	setFd(int _clientFd);
	void	setAdress(struct sockaddr_in clientAddr);
	void	setNickname(std::string nickname);
	void	setIsAuth(int auth);

	const std::string	getNickname(void);
	int					getAuth(void);
	int					getFd(void);
};
