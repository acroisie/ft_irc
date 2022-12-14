#include "../../includes/Server.hpp"

void	Server::user(Client &client)
{
	client.setUsername(client.getTokens()[1]);
	client.setRealname(client.getTokens()[4]);
}