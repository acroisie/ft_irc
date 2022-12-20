#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::invite(Client &client)
{
	if (segvGuard(client))
		return ;
	if (client.getIsOp())
	{
		map<int, Client>::iterator it = _clientMap.begin();
		while (it != _clientMap.end())
		{
			if (it->second.getNickname().compare(client.getTokens()[1]) == 0)
			{
				it->second.setReply(RPL_INVITING(client.getNickname(), client.getTokens()[1], client.getTokens()[2]));
				FD_SET(it->second.getFd(), &_writeFds);
				_channelMap[client.getTokens()[2]]->setInvited(client.getTokens()[1]);
				break;
			}
			it++;
		}
		if (it == _clientMap.end())
			client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
	}
	else
		client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
}