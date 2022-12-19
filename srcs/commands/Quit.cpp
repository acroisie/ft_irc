#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::quit(Client &client)
{
	close(client.getFd());
	FD_CLR(client.getFd(), &_clientFds);
	FD_CLR(client.getFd(), &_readFds);
	cout << "\r" << client.getNickname() << " leave the server" << endl;
	_clientMap.erase(client.getFd());
}