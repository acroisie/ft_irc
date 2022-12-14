#include "../../includes/Server.hpp"



void	Server::nick(Client &client)
{
	if (!nickAlreadyUse(client)) 
	{
		for (size_t i = 0; i < client.getTokens()[1].size(); i++)
		{
			if (!((isalnum(client.getTokens()[1][i])) || (client.getTokens()[1][i] == '-') || (client.getTokens()[1][i] == '_')))
			{
				client.setReply(ERR_ERRONEUSNICKNAME(client.getNickname(), client.getTokens()[1]));
				return;
			}
		}	
		client.setReply(RPL_NICK(client.getNickname(), client.getTokens()[1]));
		client.setNickname(client.getTokens()[1]);
	}
	else
	{
		client.setReply(ERR_NICKNAMEINUSE(client.getNickname(), client.getTokens()[1]));
		return;
	}
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