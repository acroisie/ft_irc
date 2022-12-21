#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::pass(Client &client)
{
	if (client.getTokens().size() < 2)
		return ;
	if (client.getTokens()[1] == _password)
		client.setCheckAuth("pass");
}