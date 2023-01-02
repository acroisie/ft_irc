#include "../../includes/Server.hpp"

void	Server::part(Client &client)
{
	if (segvGuard(client))
		return ;
	string chlName = client.getTokens()[1];
	if (_channelMap.count(client.getTokens()[1]))
	{
		if (!(_channelMap[chlName]->clientIsOnChan(client)))
			client.setReply(ERR_NOTONCHANNEL(client.getNickname(), chlName));
		else
		{
			client.setReply(RPL_PART(client.getNickname(), chlName));
			notice(client, chlName, RPL_PART(client.getNickname(), chlName));
			_channelMap[chlName]->eraseClient(client);
			if (_channelMap[chlName]->getFdVector().empty())
				_channelMap.erase(chlName);
		}
	}
	else
		client.setReply(ERR_NOSUCHCHANNEL(client.getNickname(), chlName));
}