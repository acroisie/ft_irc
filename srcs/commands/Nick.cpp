#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::nick(Client &client)
{
	if (segvGuard(client))
		return ;
	if (!nickAlreadyUse(client)) 
	{
		for (size_t i = 0; i < client.getTokens()[1].size(); i++)
		{
			if (!((isalnum(client.getTokens()[1][i])) || (client.getTokens()[1][i] == '-') || (client.getTokens()[1][i] == '_')))
			{
				client.setReply(ERR_ERRONEUSNICKNAME(client.getNickname(), client.getTokens()[1]));
				client.setIsAuth(-1);
				return;
			}
		}	
		client.setReply(RPL_NICK(client.getNickname(), client.getTokens()[1]));
		client.setNickname(client.getTokens()[1]);
		client.setCheckAuth("nick");
	}
	else
	{
		client.setReply(ERR_NICKNAMEINUSE(client.getNickname(), client.getTokens()[1]));
		return;
	}
	if (client.authIsValid())
	{
		client.setReply(RPL_WELCOME(client.getNickname()));
		client.setIsAuth(1);
	}
	std::cout << client.getCheckAuth("pass") <<  " here\n";
	if (client.getCheckAuth("pass") == 0)
	{
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));
		client.setIsAuth(-1);
	}
}