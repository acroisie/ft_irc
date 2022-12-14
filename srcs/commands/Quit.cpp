#include "../../includes/Server.hpp"

void	Server::quit(Client &client)
{
	close(client.getFd());
	FD_CLR(client.getFd(), &_clientFds);
	FD_CLR(client.getFd(), &_readFds);
	std::cout << "\r" << client.getNickname() << " leave the server" << std::endl;
	_clientMap.erase(client.getFd());
}