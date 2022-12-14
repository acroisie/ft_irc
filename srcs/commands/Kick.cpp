#include "../../includes/Server.hpp"


void	Server::kick(Client &client)
{
	// int fd = _channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2]);
	
	if (client.getIsOp())
	{
		_clientMap[_channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2])].setReply(RPL_KICK(client.getTokens()[1], client.getTokens()[2], "TEST"));
		// FD_SET(_clientMap[_channelMap[client.getTokens()[1]]->getNameFd(client.getTokens()[2])], &_writeFds);
	}
}