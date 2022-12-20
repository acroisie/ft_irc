#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::mode(Client &client)
{
	if (!client.getIsOp())
	{
		client.setReply(ERR_CHANOPRIVSNEEDED(client.getNickname(),client.getTokens()[1]));
		return ;
	}
	if (client.getTokens().size() > 2)
	{
		if ((client.getTokens()[2].compare("+i")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeI("+i");
			notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
			client.getTokens()[1], "+i"));
			client.setReply(RPL_MODE(client.getNickname(),client.getTokens()[1], "+i"));
		}

		else if ((client.getTokens()[2].compare("-i")) == 0)
		{
			_channelMap[client.getTokens()[1]]->unsetModeI();
			notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
			client.getTokens()[1], "-i"));
			client.setReply(RPL_MODE(client.getNickname(), client.getTokens()[1], "-i"));
		}
		else if ((client.getTokens()[2].compare("+k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("+k");
			if (client.getTokens().size() > 3)
			{
				_channelMap[client.getTokens()[1]]->setPassword(client.getTokens()[3]);
				notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
				client.getTokens()[1], "+k"));
				client.setReply(RPL_MODE(client.getNickname(), client.getTokens()[1], "+k"));
			}
		}
		else if ((client.getTokens()[2].compare("-k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("-k");
			_channelMap[client.getTokens()[1]]->getPassword().clear();
			client.setReply(RPL_MODE(client.getNickname(), client.getTokens()[1], "-k"));
			notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
			client.getTokens()[1], "-k"));
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
	// else
	// 	client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[0]));
}
