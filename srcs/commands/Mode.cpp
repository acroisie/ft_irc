#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::mode(Client &client)
{
	if (client.getTokens().size() >= 3)
	{
		if (client.getTokens()[3] == "+i")
			_channelMap[client.getTokens()[2]]->setMode("+i");
	}
}