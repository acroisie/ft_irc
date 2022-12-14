#include "../../includes/Server.hpp"

void	Server::ping(Client &client)
{
	client.setReply(RPL_PING(client.getTokens()[1]));
}