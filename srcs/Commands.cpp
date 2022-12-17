#include	"../includes/Server.hpp"
using		namespace std;

/*-----------------MemberFunctions------------------*/

void	Server::execCommand(Client &client)
{
	map<string, void (Server::*)(Client &)>::iterator it = _commandMap.find(client.getTokens()[0]);
	if (it != _commandMap.end())
		(this->*(it->second))(client);
}

bool	Server::nickAlreadyUse(Client &client)
{
	for (map<int, Client>::iterator it = _clientMap.begin(); it != _clientMap.end(); it++)
	{
		if (!it->second.getNickname().compare(client.getTokens()[1]))
			return (1);
	}
	return (0);
}




