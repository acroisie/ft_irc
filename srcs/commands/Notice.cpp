#include "../../includes/Server.hpp"

void Server::notice(Client &client)
{
	std::string	msg;
	std::vector<std::string>::iterator it = client.getTokens().begin();
	it += 2;
	while (true)
	{
		msg += *it;
		it++;
		if (it == client.getTokens().end())
			break;
		msg += " ";
	}
	if (client.getTokens()[1].c_str()[0] == '#')
	{
		std::string	chlName = client.getTokens()[1];
		if (_channelMap.find(chlName) != _channelMap.end())
		{			
			for(std::vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
			{
				if (*it != client.getFd())
				{
					_clientMap[*it].setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg));
					FD_SET(_clientMap[*it].getFd(), &_writeFds);
				}
			}
		}
	}
	else
	{
		std::map<int, Client>::iterator it = _clientMap.begin();
		while (it != _clientMap.end())
		{
			if (it->second.getNickname().compare(client.getTokens()[1]) == 0)
			{
				it->second.setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg));
				FD_SET(it->second.getFd(), &_writeFds);
				break;
			}
			it++;
		}
	}
}

void Server::notice(Client &client, std::string chlName, std::string msg)
{	
	for(std::vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
	{
		if (*it != client.getFd())
		{
			_clientMap[*it].setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg));
			FD_SET(_clientMap[*it].getFd(), &_writeFds);
		}
	}
}
