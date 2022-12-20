#include	"../../includes/Server.hpp"
using		namespace std;

bool	Server::modeCheck(string chlName, Client &client)
{
	if ((_channelMap[chlName]->getModeI().compare("+i")) == 0)
	{
		vector<string>::iterator it = find(_channelMap[chlName]->getInvitedList().begin(), \
		 _channelMap[chlName]->getInvitedList().end(), client.getNickname());
		if (it != _channelMap[chlName]->getInvitedList().end())
			return (true);
		else
			client.setReply(ERR_NOTONCHANNEL(client.getNickname(), chlName));
			return (false);
	}
	else
		return (true);
}

void	Server::join(Client &client)
{
	if (segvGuard(client))
		return ;
	size_t pos = 0;
	string tab[3] = {"^G"," ", ","};
	string chlName = client.getTokens()[1].c_str();
	// string password;
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
		if (!_channelMap.count(chlName))
		{
			client.setPrefix("@");
			client.setIsOp(1);
			_channelMap[chlName] = new Channel();
			_channelMap[chlName]->setSymbol("=");
			_channelMap[chlName]->setName(chlName);
			_channelMap[chlName]->addClientFd(client.getFd());
			_channelMap[chlName]->setNameFd(client.getNickname(), client.getFd());
			if (client.getTokens().size() > 2)
			{
				_channelMap[chlName]->setModeK("+k");
				_channelMap[chlName]->setPassword(client.getTokens()[2]);
				
			}
			replyJoin(client, _channelMap[chlName]);
		}
		else if (_channelMap.count(chlName))
		{
			if (_channelMap[chlName]->getModeK().compare("+k") == 0)
			{
				if (!_channelMap[chlName]->verifPassord(client))
					return;
			}
			if (_channelMap[chlName]->clientIsOnChan(client))
				return ;
			if (!_channelMap[chlName]->clientIsBanned(client))
			{
				if (modeCheck(chlName, client))
				{
					_channelMap[chlName]->addClientFd(client.getFd());
					_channelMap[chlName]->setNameFd(client.getNickname(), client.getFd());
					notice(client, chlName, RPL_JOIN(client.getNickname(), chlName));
					replyJoin(client, _channelMap[chlName]);
				}
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
