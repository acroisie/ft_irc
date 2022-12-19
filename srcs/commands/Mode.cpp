#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::mode(Client &client)
{
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
			client.setReply(RPL_MODE(client.getNickname(),client.getTokens()[1], "-i"));
		}
		else if ((client.getTokens()[2].compare("+k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("+k");
			if (client.getTokens().size() > 3)
			{
				_channelMap[client.getTokens()[1]]->setPassword(client.getTokens()[3]);
				notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
				client.getTokens()[1], "+k"));
				client.setReply(RPL_MODE(client.getNickname(),client.getTokens()[1], "+k"));
			}
		}
		else if ((client.getTokens()[2].compare("-k")) == 0)
		{
			_channelMap[client.getTokens()[1]]->setModeK("-k");
			_channelMap[client.getTokens()[1]]->getPassword().clear();
			client.setReply(RPL_MODE(client.getNickname(),client.getTokens()[1], "-k"));
			notice(client, client.getTokens()[1], RPL_MODE(client.getNickname(), \
			client.getTokens()[1], "-k"));
		}
	}
}