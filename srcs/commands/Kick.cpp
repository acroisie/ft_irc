#include "../../includes/Server.hpp"


void	Server::kick(Client &client)
{
	(void)client;
	int fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2]); ;
	if (!fd)
	{

		
		std::cout << "not found\n";
		return;

	}
	std::cout << _clientMap[fd].getNickname() << std::endl;

	if (client.getIsOp())
	{
		std::cout << "Flag 1" << std::endl;
		//client.setReply(RPL_KICK(client.getNickname(),	_clientMap[fd].getNickname(), client.getTokens()[1]));
		//notice(client, client.getTokens()[1], RPL_KICK(client.getNickname(),	_clientMap[fd].getNickname(), client.getTokens()[1]));

		std::cout << _clientMap[fd].getReply() << std::endl;;
	}
}

int Server::searchByNick(std::string name)
{
	for (std::map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
	{
		std::cout << "-> " <<it->second.getNickname() << " " <<it->second.getFd() << "\n";
		std::cout << "name : " << name << "\n";

		if (!it->second.getNickname().compare(name))
			return (it->second.getFd());
	}
	return(0);
}