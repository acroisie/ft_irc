#include	"../includes/Client.hpp"

/*---------------Constructor/Destructor--------------*/

Client::Client(void){}

Client::~Client(){}

/*---------------------Setters-----------------------*/

void	Client::setNickname(std::string nickname)
{
	_nickname =  nickname;
}

void	Client::setFd(int clientFd)
{
	_clientFd =  clientFd;
}

void	Client::setAdress(struct sockaddr_in clientAddr)
{
	_clientAddr =  clientAddr;
}

/*----------------------Getters---------------------*/

const std::string	Client::getNickname(void)
{
	return (_nickname);
}

/*-----------------MemberFunctions------------------*/