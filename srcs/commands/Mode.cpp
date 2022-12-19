#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::mode(Client &client)
{
	if (client.getTokens().size() > 2)
	{
		if ((client.getTokens()[2].compare("+i")) == 0)
			_channelMap[client.getTokens()[1]]->setMode("+i");
	}
}