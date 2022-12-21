#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return ;

	for (map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
	{
		if (it->second.getFd() != client.getFd())
		{
			if (it->second.getUsername().compare(client.getTokens()[1]) == 0)
			{
				client.setReply(ERR_ALREADYREGISTERED(client.getTokens()[1]));
				return;
			}
		}
	}
	client.setUsername(client.getTokens()[1]);
	client.setCheckAuth("user");
	if (client.authIsValid())
	{
		client.setReply(RPL_WELCOME(client.getNickname()));
		client.setIsAuth(1);
	}
	else
		client.setIsAuth(-2);
}