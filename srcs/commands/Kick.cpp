#include "../../includes/Server.hpp"


void	Server::kick(Client &client)
{
	std::string	comment;
	std::vector<std::string>::iterator it = client.getTokens().begin();
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
		client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
	else if (client.getIsOp())
	{
		client.setReply(RPL_KICK(client.getNickname(), _clientMap[fd].getNickname(), client.getTokens()[1], (comment.empty() ? "" : comment)));
		notice(client, client.getTokens()[1], RPL_KICK(client.getNickname(), _clientMap[fd].getNickname(), client.getTokens()[1], (comment.empty() ? "" : comment)));
	}
}
