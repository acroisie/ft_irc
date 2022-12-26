#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return ;
	// for (map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
	// {
	// 	if (it->second.getUsername().compare(client.getUsername()))
	// 	{
	// 		client.setReply(ERR_ALREADYREGISTERED(client.getNickname()));
	// 		return;
	// 	}
	// }
	client.setUsername(client.getTokens()[1]);
	if(client.getAuth() == 0)
	{
		client.setIsAuth(-1);
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));	
	}
	else if (client.getAuth() == 1)
	{
		client.setReply(RPL_WELCOME(client.getNickname()));
		client.setIsAuth(2);
	}
}