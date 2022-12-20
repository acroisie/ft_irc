#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::privMsg(Client &client)
{
	if (segvGuard(client))
		return ;
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
			if(_channelMap[chlName]->clientIsOnChan(client))
			{
				for(vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
				{
					if (*it != client.getFd())
					{
						_clientMap[*it].setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg.substr(1, msg.size()).c_str()));
						FD_SET(_clientMap[*it].getFd(), &_writeFds);
					}
				}
			}
			else
			{
				client.setReply(ERR_CANNOTSENDTOCHAN(client.getNickname(), chlName));
				FD_SET(client.getFd(), &_writeFds);
			}
		}
		else
			client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
	}
	else
	{
		map<int, Client>::iterator it = _clientMap.begin();
		while (it != _clientMap.end())
		{
			if (it->second.getNickname().compare(client.getTokens()[1]) == 0)
			{
				it->second.setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg.substr(1, msg.size()).c_str()));
				FD_SET(it->second.getFd(), &_writeFds);
				break;
			}
			it++;
		}
		if (it == _clientMap.end())
			client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
	}
}