#include	"../includes/Channel.hpp"

/*---------------Constructor/Destructor--------------*/

Channel::Channel(Client &client)
{
	_clientList.push_back(client.getFd());
	_name = client.getTokens()[1];
	client.setIsOp(1);
}
Channel::~Channel(){}

/*---------------------Setters-----------------------*/

void				Channel::setClientList(int clientFd){_clientList.push_back(clientFd);}

/*----------------------Getters---------------------*/

std::vector<int>	Channel::getClientList(void){return (_clientList);}

/*-----------------MemberFunctions------------------*/