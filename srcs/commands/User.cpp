#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::user(Client &client)
{
	if (segvGuard(client))
		return ;
	client.setUsername(client.getTokens()[1]);
	client.setRealname(client.getTokens()[4]);
}