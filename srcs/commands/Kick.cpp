#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::kick(Client &client)
{
	if (segvGuard(client))
		return ;
	if (_channelMap.count(client.getTokens()[1]))
	{
		if (_channelMap[client.getTokens()[1]]->isOp(client))
		{	
			string	comment;
			vector<string>::iterator it = client.getTokens().begin();
			if (client.getTokens().size() > 3)
			{
				it += 3;
				while (true)
				{
					comment += *it;
					it++;
					if (it == client.getTokens().end())
						break;
					comment += " ";
				}
			}
			int fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2]); ;
			if (!fd)
			{
				client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
				return ;
			}
			client.setReply(RPL_KICK(client.getNickname(), _clientMap[fd].getNickname(), client.getTokens()[1], (comment.empty() ? "" : comment)));
			notice(client, client.getTokens()[1], RPL_KICK(client.getNickname(), _clientMap[fd].getNickname(), client.getTokens()[1], (comment.empty() ? "" : comment)));
			_channelMap[client.getTokens()[1]]->eraseClient(_clientMap[fd]);
			_channelMap[client.getTokens()[1]]->unsetInvited(client.getTokens()[2]);
		}
		else
			client.setReply(ERR_CHANOPRIVSNEEDED(client.getNickname(), client.getTokens()[1]));
	}
	else 
		client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
}

