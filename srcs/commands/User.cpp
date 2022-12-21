#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return ;

	for (map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
	{
		if (it->second.getUsername().compare(client.getUsername()))
		{
			client.setReply(ERR_ALREADYREGISTERED(client.getNickname()));
			return;
		}
	}
	client.setUsername(client.getTokens()[1]);
}