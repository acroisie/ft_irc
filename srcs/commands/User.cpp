#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return ;
	if(_clientMap[client.getFd()].getUsername().compare(client.getUsername()) == 0)
		client.setReply(ERR_ALREADYREGISTERED(client.getNickname()));
	client.setUsername(client.getTokens()[1]);
}