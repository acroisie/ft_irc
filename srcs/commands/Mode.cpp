#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::notifAll(Client &client, string mode)
{
	notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
	client.getTokens()[1], mode));
	client.setReply(RPL_MODE(client.getNickname(),client.getTokens()[1], mode));
}
void	Server::mode(Client &client)
{
		if (segvGuard(client))
		return ;
	if (client.getTokens().size() > 2)
	{
		if (!client.getIsOp())
		{
			client.setReply(ERR_CHANOPRIVSNEEDED(client.getNickname(),client.getTokens()[1]));
			return ;
		}
		if ((client.getTokens()[2].compare("+i")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeI("+i");
			notifAll(client, "+i");
		}
		else if ((client.getTokens()[2].compare("-i")) == 0)
		{
			_channelMap[client.getTokens()[1]]->unsetModeI();
			notifAll(client, "-i");
		}

		if ((client.getTokens()[2].compare("+k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("+k");
			if (client.getTokens().size() > 3)
			{
				_channelMap[client.getTokens()[1]]->setPassword(client.getTokens()[3]);
				notifAll(client, "+k");
			}
		}
		else if ((client.getTokens()[2].compare("-k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("-k");
			_channelMap[client.getTokens()[1]]->getPassword().clear();
			notifAll(client, "-k");
		}
		int fd;
		if (client.getTokens().size() > 3)
		{
			fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[3]);
			if (!fd)
				return;
		}
		if ((client.getTokens()[2].compare("+o")) == 0)
		{
				_clientMap[fd].setPrefix("@");
				_clientMap[fd].setIsOp(1);
				notice(client, client.getTokens()[1], RPL_MODEO(client.getPrefix() + client.getNickname(), \
				client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
				client.setReply(RPL_MODEO(client.getPrefix() + client.getNickname(), client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
		}
		else if ((client.getTokens()[2].compare("-o")) == 0)
		{
			_clientMap[fd].getPrefix().clear();
			_clientMap[fd].setIsOp(0);
			notice(client, client.getTokens()[1], RPL_MODEO(client.getPrefix() + client.getNickname(), \
			client.getTokens()[1], "-o",_clientMap[fd].getNickname()));
			client.setReply(RPL_MODEO(client.getPrefix() + client.getNickname(), client.getTokens()[1], "-o",_clientMap[fd].getNickname()));
		}
	}
}
