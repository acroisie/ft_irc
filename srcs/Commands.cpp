#include "../includes/Server.hpp"

/*-----------------MemberFunctions------------------*/

void	Server::execCommand(Client &client)
{
	std::map<std::string, void (Server::*)(Client &)>::iterator it = _commandMap.find(client.getTokens()[0]);
	if (it != _commandMap.end())
		(this->*(it->second))(client);
}



std::string	Server::membershipList(Channel *channel)
{
	std::string buff;
	for(std::vector<int>::iterator it = channel->getFdVector().begin(); it != channel->getFdVector().end(); it++)
	{
		buff += _clientMap[*it].getPrefix() + _clientMap[*it].getNickname();
		if (it == channel->getFdVector().end())
			break;
		buff += " ";
	}
	return (buff);
}

void	Server::replyJoin(Client &client, Channel *channel)
{
		client.setReply(RPL_JOIN(client.getNickname(), channel->getName()));
		if (channel->getTopic().empty())
			client.setReply(RPL_NOTOPIC(client.getNickname(), channel->getName()));
		else
			client.setReply(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
		client.setReply(RPL_NAMEPLY(client.getNickname(), \
									 channel->getSymbol(), \
									 channel->getName(), \
									 membershipList(channel)));
		client.setReply(RPL_ENDOFNAME(client.getNickname(), channel->getName()));
}


