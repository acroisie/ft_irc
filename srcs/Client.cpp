#include	"../includes/Client.hpp"

/*---------------Constructor/Destructor--------------*/

Client::Client(void){}

Client::~Client(){}

/*---------------------Setters-----------------------*/

void	Client::setFd(int clientFd)
{
	_clientFd =  clientFd;
}

void	Client::setAdress(struct sockaddr_in clientAddr)
{
	_clientAddr =  clientAddr;
}

/*-----------------MemberFunctions------------------*/