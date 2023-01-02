#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::nick(Client &client)
{
	if (segvGuard(client))
		return ;
	if (client.getAuth() == 0)
		return;
	if (!nickAlreadyUse(client)) 
	{
		for (size_t i = 0; i < client.getTokens()[1].size(); i++)
		{
			if (!((isalnum(client.getTokens()[1][i])) || (client.getTokens()[1][i] == '-') || (client.getTokens()[1][i] == '_')))
			{
				client.setReply(ERR_ERRONEUSNICKNAME(client.getNickname(), client.getTokens()[1]));
				return;
			}
		}	
		client.setReply(RPL_NICK(client.getNickname(), client.getTokens()[1]));
		for (map<string, Channel *>::iterator it = _channelMap.begin(); it != _channelMap.end(); it++)
		{
			if (it->second->clientIsOnChan(client))
			{
				bool isOp = false;
				if (it->second->isOp(client))
					isOp = true;
				notice(client, it->second->getName(), RPL_NICK(client.getNickname(), client.getTokens()[1]));
				it->second->eraseClient(client);
				it->second->addClientFd(client.getFd());
				it->second->setNameFd(client.getTokens()[1], client.getFd());
				if (isOp)
					it->second->addOp(client);
			}
		}
		client.setNickname(client.getTokens()[1]);
		client.setNickOk(1);
		if (client.getUserOk())
		{
			client.setReply(RPL_WELCOME(client.getNickname()));
			return;
		}
	}
	else
	{
		client.setReply(ERR_NICKNAMEINUSE(client.getNickname(), client.getTokens()[1]));
		client.setNickOk(0);
		return;
	}
}