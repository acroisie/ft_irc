#include "../includes/Server.hpp"

/*---------------Constructor/Destructor--------------*/

/*---------------------Setters-----------------------*/

/*----------------------Getters---------------------*/

/*-----------------MemberFunctions------------------*/

void	Server::execCommand(Client &client)
{
	std::map<std::string, void (Server::*)(Client &)>::iterator it = _commandMap.find(client.getTokens()[0]);
	if (it != _commandMap.end())
		(this->*(it->second))(client);
}

void	Server::nick(Client &client)
{
	client.setNickname(client.getTokens()[1]);
	if(!client.getAuth())
	{
		client.setIsAuth(-1);
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));	
	}
	else
		client.setReply(RPL_WELCOME(client.getNickname()));
}

void	Server::pass(Client &client)
{
	// std::cout << client.getTokens()[0];
	if (client.getTokens()[1] == _password)
		client.setIsAuth(1);
	else
		client.setIsAuth(-1);

}

void	Server::cap(Client &client)
{
	(void)client;
}

void	Server::user(Client &client)
{
	client.setUsername(client.getTokens()[1]);
	client.setRealname(client.getTokens()[4]);
}

std::string	Server::membershipList(Channel *channel)
{
	std::string buff;
	for(std::vector<int>::iterator it = channel->getFdVector().begin(); it != channel->getFdVector().end(); it++)
	{
		buff +=   _clientMap[*it].getPrefix() + _clientMap[*it].getNickname();
		if (it == channel->getFdVector().end())
			break;
		buff += " ";
	}
	return (buff);
}

void	Server::replyJoin(Client &client, Channel *channel)
{
		client.setReply(RPL_JOIN(client.getNickname(), channel->getName()));
		client.setReply(RPL_TOPIC(client.getNickname(), channel->getName(), channel->getTopic()));
		client.setReply(RPL_NAMEPLY(client.getNickname(), \
									 channel->getSymbol(), \
									 channel->getName(), \
									 membershipList(channel)));
		client.setReply(RPL_ENDOFNAME(client.getNickname(), channel->getName()));
}

void	Server::join(Client &client)
{
	std::string chlName = client.getTokens()[1].c_str();
	if (chlName[0] == '#')
	{
		if ((chlName.find(' ') || chlName.find(',') || chlName.find('^G')) != std::string::npos)
			
	}

	if (!_channelMap[chlName])
	{
		client.setPrefix("@");
		_channelMap[chlName] = new Channel(client);
		_channelMap[chlName]->setSymbol("=");
		_channelMap[chlName]->setFd(client.getFd());
		replyJoin(client, _channelMap[chlName]);
	}
	else if (_channelMap[chlName])
	{
		_channelMap[chlName]->setFd(client.getFd());
		replyJoin(client, _channelMap[chlName]);
	}
}

void	Server::quit(Client &client)
{
	close(client.getFd());
	FD_CLR(client.getFd(), &_clientFds);
	FD_CLR(client.getFd(), &_readFds);
	std::cout << "\rBye bye " << client.getNickname() << "!" << std::endl;
}

void	Server::ping(Client &client)
{
	client.setReply(RPL_PING(client.getTokens()[1]));
}

void	Server::privMsg(Client &client)
{
	std::string	msg;
	std::cout << "Flag 1" << std::endl;
	//std::vector<std::string>::iterator it = client.getTokens().begin();
	for (std::vector<std::string>::iterator it = client.getTokens().begin(); it != client.getTokens().end() ;it++)
	{
		msg += *it;
	}
	std::cout << "Flag 2" << std::endl;
	
	if (client.getTokens()[1].c_str()[0] == '#')
	{
		std::string	chlName = client.getTokens()[1];
		for(std::vector<int>::iterator it = _channelMap[chlName]->getFdVector().begin(); it != _channelMap[chlName]->getFdVector().end(); it++)
		{
			if (*it != client.getFd())
			{
				_clientMap[*it].setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg));
				FD_SET(_clientMap[*it].getFd(), &_writeFds);
			}
		}
	std::cout << "Flag 3" << std::endl;
	}
	else
	{
		std::map<int, Client>::iterator it = _clientMap.begin();
		while (it != _clientMap.end())
		{
			if (it->second.getNickname().compare(client.getTokens()[1]) == 0)
			{
				it->second.setReply(RPL_PRIVMSG(client.getNickname(), client.getTokens()[1], msg));
				FD_SET(it->second.getFd(), &_writeFds);
				break;
			}
			it++;
		}

	}
	//erreur le nick n'existe pas
}
