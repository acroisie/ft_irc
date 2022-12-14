#include "../../includes/Server.hpp"



void	Server::nick(Client &client)
{
	client.setReply(RPL_NICK(client.getNickname(), client.getTokens()[1]));
	client.setNickname(client.getTokens()[1]);
	if(!client.getAuth())
	{
		client.setIsAuth(-1);
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));	
	}
	else
		client.setReply(RPL_WELCOME(client.getNickname()));
}