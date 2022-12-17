#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::join(Client &client)
{
	size_t pos = 0;
	string tab[3] = {"^G"," ", ","};
	string chlName = client.getTokens()[1].c_str();
	string password;
	if (client.getTokens().size() > 2)
	{
		password = client.getTokens()[2];

	}
	if (chlName[0] == '#')
	{
		for (size_t i = 0; i <= tab->size(); i++)
		{
			if ((pos = chlName.find(tab[i])) != string::npos)
			{
				chlName = chlName.substr(0, pos);
				break;
			}
		}
		if (!_channelMap[chlName])
		{
			client.setPrefix("@");
			client.setIsOp(1);
			_channelMap[chlName] = new Channel();
			_channelMap[chlName]->setSymbol("=");
			_channelMap[chlName]->setName(chlName);
			_channelMap[chlName]->setFd(client.getFd());
			_channelMap[chlName]->setNameFd(client.getNickname(), client.getFd());
			replyJoin(client, _channelMap[chlName]);
		}
		else if (_channelMap[chlName])
		{
			if (!_channelMap[chlName]->clientIsBanned(client))
			{
				_channelMap[chlName]->setFd(client.getFd());
				_channelMap[chlName]->setNameFd(client.getNickname(), client.getFd());
				notice(client, chlName, RPL_JOIN(client.getNickname(), chlName));
				replyJoin(client, _channelMap[chlName]);
			}
			else
				client.setReply(ERR_BANNEDFROMCHAN(client.getNickname(), chlName));
		}
	}
	else
		client.setReply(ERR_BADCHANMASK(client.getTokens()[1]));
		
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

string	Server::membershipList(Channel *channel)
{
	string buff;
	for(vector<int>::iterator it = channel->getFdVector().begin(); it != channel->getFdVector().end(); it++)
	{
		buff += _clientMap[*it].getPrefix() + _clientMap[*it].getNickname();
		if (it == channel->getFdVector().end())
			break;
		buff += " ";
	}
	return (buff);
}
