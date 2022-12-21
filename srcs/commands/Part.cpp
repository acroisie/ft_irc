#include "../../includes/Server.hpp"

void	Server::part(Client &client)
{
	if (segvGuard(client))
		return ;
	string chalname = client.getTokens()[1];
	if (_channelMap[chalname])
	{
		if (!(_channelMap[chalname]->clientIsOnChan(client)))
		{
			client.setReply(ERR_NOTONCHANNEL(client.getNickname(), chalname));
			return;
		}
		else
		{
			client.setReply(RPL_PART(client.getNickname(), chalname));
			notice(client, chalname, RPL_PART(client.getNickname(), chalname));
			_channelMap[chalname]->eraseClient(client);
			if (_channelMap[chalname]->getFdVector().empty())
			{
				_channelMap.erase(chalname);
				// std::cout << "clear tab\n";
			}
		}
	}
	else
	{
		client.setReply(ERR_NOSUCHCHANNEL(client.getNickname(), chalname));
		return;
	}
}

