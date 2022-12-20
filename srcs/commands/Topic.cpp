#include	"../../includes/Server.hpp"
using		namespace std;

void	Server::topic(Client &client)
{
	std::string topic;

	if (segvGuard(client))
		return ;
	if (!_channelMap[client.getTokens()[1]]->isOp(client))
	{
		client.setReply(ERR_CHANOPRIVSNEEDED(client.getNickname(), client.getTokens()[1]));
		return;
	}
	if (!_channelMap.count(client.getTokens()[1]))
	{
		client.setReply(ERR_NOSUCHCHANNEL(client.getNickname(), ));
		return ;
	}
	if (!_channelMap[client.getTokens()[1]]->clientIsOnChan(client))
	{
		client.setReply(ERR_NOTONCHANNEL(client.getNickname(), client.getTokens()[1]));
		return ;
	}
	if (client.getTokens().size() == 3)
	{
		topic =  client.getTokens()[2].substr(1,  client.getTokens()[2].size());
		_channelMap[client.getTokens()[1]]->setTopic(topic);
		if (topic.compare(":") == 0)
			_channelMap[client.getTokens()[1]]->setTopic("");
		client.setReply(RPL_TOPICC(client.getNickname(), client.getTokens()[1], _channelMap[client.getTokens()[1]]->getTopic()));
		notice(client,client.getTokens()[1], RPL_TOPICC(client.getNickname(), client.getTokens()[1], _channelMap[client.getTokens()[1]]->getTopic()));
	}
	else if (client.getTokens().size() == 2)
	{
		if (_channelMap[client.getTokens()[1]]->getTopic().empty())
			client.setReply(RPL_NOTOPIC(client.getNickname(), client.getTokens()[1]));
		else
			client.setReply(RPL_TOPIC(client.getNickname(), client.getTokens()[1], _channelMap[client.getTokens()[1]]->getTopic()));
	}
}