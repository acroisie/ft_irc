#include "../../includes/Server.hpp"

void	Server::pass(Client &client)
{
	if (client.getTokens()[1] == _password)
		client.setIsAuth(1);
	else
		client.setIsAuth(0);
}