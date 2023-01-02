#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return;
	client.setUsername(client.getTokens()[1]);
	if(client.getAuth() == 0)
	{
		client.setIsAuth(-1);
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));
		return;
	}
	else if (client.getNickOk() && client.getUserOk() == 0)
	{
		client.setReply(RPL_WELCOME(client.getNickname()));
	}
	client.setUserOk(1);

}