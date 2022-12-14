#include "../includes/Server.hpp"

void	Server::join(Client &client)
{
	size_t pos = 0;
	std::string tab[3] = {"^G"," ", ","};
	std::string chlName = client.getTokens()[1].c_str();
	std::string password;
	if (client.getTokens().size() > 2)
	{
		password = client.getTokens()[2];

	}
	if (chlName[0] == '#')
	{
		for (size_t i = 0; i <= tab->size(); i++)
		{
			if ((pos = chlName.find(tab[i])) != std::string::npos)
			{
				chlName = chlName.substr(0, pos);
				break;
			}
		}
		if (!_channelMap[chlName])
		{
			client.setPrefix("@");
			_channelMap[chlName] = new Channel();
			_channelMap[chlName]->setSymbol("=");
			_channelMap[chlName]->setName(chlName);
			_channelMap[chlName]->setFd(client.getFd());
			_channelMap[chlName]->setNameFd(client.getNickname(), client.getFd());
			replyJoin(client, _channelMap[chlName]);
		}
		else if (_channelMap[chlName])
		{
			_channelMap[chlName]->setFd(client.getFd());
			replyJoin(client, _channelMap[chlName]);
		}
	}
	else
		client.setReply(ERR_BADCHANMASK(client.getTokens()[1]));
		
}