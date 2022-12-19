#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::topic(Client &client)
{
	
	std::string chlname = client.getTokens()[1];
	if (!_channelMap[chlname])
	{
		client.setReply(ERR_NOSUCHCHANNEL(client.getNickname(), chlname));
		return ;
	}
	else if (!_channelMap[chlname]->clientIsOnChan(client))
	{
		client.setReply(ERR_NOTONCHANNEL(client.getNickname(), chlname));
		return ;
	}
	if (client.getTokens().size() > 2)
	{
		_channelMap[chlname]->setTopic(client.getTokens()[2]);
		std::string topic =  client.getTokens()[2].substr(1,  client.getTokens()[2].size());
		client.setReply(RPL_TOPIC(client.getNickname(), chlname, topic));
		notice(client,chlname, RPL_TOPIC(client.getNickname(), chlname, topic));
	}
	(void)client;
}