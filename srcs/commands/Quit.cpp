#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::quit(Client &client)
{
	cout << "\r" << client.getNickname() << " leave the server" << endl;
	for (map<string, Channel *>::iterator it = _channelMap.begin(); it != _channelMap.end(); it++)
	{	
		if (it->second->clientIsOnChan(client))
			it->second->eraseClient(client);
	}
	close(client.getFd());
	FD_CLR(client.getFd(), &_clientFds);
	FD_CLR(client.getFd(), &_readFds);
	_clientMap.erase(client.getFd());
}