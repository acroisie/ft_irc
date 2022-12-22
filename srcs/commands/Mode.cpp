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
	std::string modeList[6] = {"+i", "-i", "+k", "-k", "+o", "-o"};
	if (_channelMap.count(client.getTokens()[1]))
	{
		if (client.getTokens().size() > 2)
		{
			int flag = 0;
			for (size_t i = 0; i != 6 ; i++)
			{
				if (client.getTokens()[2].compare(modeList[i]) == 0)
					flag = 1;
			}
			if (flag == 0)
				return;
			if (!_channelMap[client.getTokens()[1]]->isOp(client))
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
				if (client.getTokens().size() > 3)
				{
					_channelMap[client.getTokens()[1]]->setModeK("+k");
					_channelMap[client.getTokens()[1]]->setPassword(client.getTokens()[3]);
					notifAll(client, "+k");
				}
				else
					client.setReply(ERR_NEEDMOREPARAMS(client.getNickname(), client.getTokens()[0]));
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
			string prefixe = "@";
			if ((client.getTokens()[2].compare("+o")) == 0)
			{
					_channelMap[client.getTokens()[1]]->addOp(_clientMap[fd]);
					notice(client, client.getTokens()[1], RPL_MODEO(prefixe + client.getNickname(), \
						client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
					client.setReply(RPL_MODEO(prefixe + client.getNickname(), \
						client.getTokens()[1], "+o", _clientMap[fd].getNickname()));
			}
			else if ((client.getTokens()[2].compare("-o")) == 0)
			{
				_channelMap[client.getTokens()[1]]->removeOp(_clientMap[fd]);
				notice(client, client.getTokens()[1], RPL_MODEO(prefixe + client.getNickname(), \
				client.getTokens()[1], "-o",_clientMap[fd].getNickname()));
				client.setReply(RPL_MODEO(prefixe + client.getNickname(), client.getTokens()[1], "-o",_clientMap[fd].getNickname()));
			}
		}
	}
	else 
	client.setReply(ERR_NOSUCHNICK(client.getNickname(), client.getTokens()[1]));
}