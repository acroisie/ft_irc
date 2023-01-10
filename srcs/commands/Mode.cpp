#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::mode(Client &client)
{
	std::string modeList[6] = {"+i", "-i", "+k", "-k", "+o", "-o"};
	int mode = -1;
	int fd;

	if (segvGuard(client))
		return ;
	if (_channelMap.count(client.getTokens()[1]))
	{
		if (client.getTokens().size() > 2)
		{
			if (!_channelMap[client.getTokens()[1]]->isOp(client))
				return (client.setReply(ERR_CHANOPRIVSNEEDED(client.getNickname(),client.getTokens()[1])));
			for (size_t i = 0; i != 6 ; i++)
				if (client.getTokens()[2].compare(modeList[i]) == 0)
					mode = i;
			switch (mode)
			{
			case 0:
				_channelMap[client.getTokens()[1]]->setModeI("+i");
				notifAll(client, "+i");
				break;
			case 1:
				_channelMap[client.getTokens()[1]]->unsetModeI();
				notifAll(client, "-i");
				break;
			case 2:
				if (client.getTokens().size() > 3)
				{
					_channelMap[client.getTokens()[1]]->setModeK("+k");
					_channelMap[client.getTokens()[1]]->setPassword(client.getTokens()[3]);
					notifAll(client, "+k");
				}
				else
					client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[0]));
				break;
			case 3:
				_channelMap[client.getTokens()[1]]->setModeK("-k");
				_channelMap[client.getTokens()[1]]->getPassword().clear();
				notifAll(client, "-k");
				break;
			case 4:
				if (client.getTokens().size() == 3)
					client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[1]));
				else if (client.getTokens().size() > 3)
				{
					if (!(fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[3])))
						return (client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1])));
					_channelMap[client.getTokens()[1]]->addOp(_clientMap[fd]);
					notice(client, client.getTokens()[1], RPL_MODEO(client.getNickname(), \
					client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
					client.setReply(RPL_MODEO(client.getNickname(), \
					client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
				}
				break;
			case 5:
				if (client.getTokens().size() == 3)
					client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[1]));
				else if (client.getTokens().size() > 3)
				{
					if (!(fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[3])))
						return (client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1])));
					_channelMap[client.getTokens()[1]]->removeOp(_clientMap[fd]);
					notice(client, client.getTokens()[1], RPL_MODEO(client.getNickname(), \
					client.getTokens()[1], "-o",_clientMap[fd].getNickname()));
					client.setReply(RPL_MODEO(client.getNickname(), client.getTokens()[1], \
					"-o",_clientMap[fd].getNickname()));
				}
				break;
			default:
				break;
			}
		}
	}
	else 
		client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
}