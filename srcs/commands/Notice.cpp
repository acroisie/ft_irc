#include "../../includes/Server.hpp"

void Server::notice(Client &client)
{
	string	msg;
	vector<string>::iterator it = client.getTokens().begin();
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
		string	chlName = client.getTokens()[1];
		if (_channelMap.find(chlName) != _channelMap.end())
		{			
			for(vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
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
		map<int, Client>::iterator it = _clientMap.begin();
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

void Server::notice(Client &client, string chlName, string msg)
{	
	for(vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
	{
		if (*it != client.getFd())
		{
			_clientMap[*it].setReply(msg);
			FD_SET(_clientMap[*it].getFd(), &_writeFds);
		}
	}
}
