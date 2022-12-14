#include "../../includes/Server.hpp"


void	Server::kick(Client &client)
{
	(void)client;
// 	int fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2]);
	
// 	if (client.getIsOp())
// 	{
// 		std::cout << "Flag 1" << std::endl;
// 		_clientMap[fd].setReply(RPL_KICK(client.getTokens()[1], client.getTokens()[2], "TEST"));
// 		std::cout << _clientMap[fd].getReply();
// 		FD_SET(fd, &_writeFds);
// 	}
}