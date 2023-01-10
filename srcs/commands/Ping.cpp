#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::ping(Client &client)
{
	if (segvGuard(client))
		return ;
	client.setReply(RPL_PING(client.getTokens()[1]));
}