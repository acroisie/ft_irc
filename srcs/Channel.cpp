#include	"../includes/Channel.hpp"
using 		namespace std;

/*---------------Constructor/Destructor--------------*/

Channel::Channel(){}
Channel::~Channel(){}

/*---------------------Setters-----------------------*/

void				Channel::setTopic(string topic){_topic = topic;}
void				Channel::setSymbol(string symbol){_symbol = symbol;}
void				Channel::setName(string name){_name = name;}
void				Channel::setPassword(string password){_password = password;}
void				Channel::setModeI(string mode){_modeI = mode;}
void				Channel::unsetModeI(void){_modeI.clear();_invitedList.clear();};
void				Channel::setModeK(string mode){_modeK = mode;}
void				Channel::setNameFd(string name, int fd){_nameFd[name] = fd;}
void				Channel::addClientFd(int fd)
{
	vector<int>::iterator it = find(_clientFd.begin(), _clientFd.end(), fd);
	if (it == _clientFd.end())
		_clientFd.push_back(fd);
}
void				Channel::setInvited(string name)
{
	vector<string>::iterator it = find(_invitedList.begin(), _invitedList.end(), name);
	if (it == _invitedList.end())
		_invitedList.push_back(name);
}
void				Channel::unsetInvited(string name)
{
	vector<string>::iterator it = find(_invitedList.begin(), _invitedList.end(), name);
	if (it != _invitedList.end())
		_invitedList.erase(it);
}

/*----------------------Getters---------------------*/

string				Channel::getTopic(void){return (_topic);}
string				Channel::getSymbol(void){return (_symbol);}
string				Channel::getName(void){return (_name);}
string				Channel::getPassword(void){return (_password);}
string				Channel::getModeI(void){return (_modeI);}
string				Channel::getModeK(void){return (_modeK);}
vector<int>			&Channel::getFdVector(void){return (_clientFd);}
vector<string>		&Channel::getInvitedList(void){return (_invitedList);}
int					Channel::getNameFd(string name){return (_nameFd[name]);}

/*-----------------MemberFunctions------------------*/

bool	Channel::clientIsBanned(Client &client)
{
	if (_bannedClientFd.find(client.getNickname()) != _bannedClientFd.end())
		return (1);
	return(0);
}

bool	Channel::clientIsOnChan(Client &client)
{
	for (vector<int>::iterator it = _clientFd.begin(); it != _clientFd.end(); it++)
	{
		if (client.getFd() == *it)
			return (1);
	}
	return (0);
}

void	Channel::eraseClient(Client &client)
{
	_nameFd.erase(client.getNickname());
	if (_opList.count(client.getNickname()))
		_opList.erase(client.getNickname());
	if (count(_invitedList.begin(), _invitedList.end(), client.getNickname()))
	{
		vector<string>::iterator it = find(_invitedList.begin(), _invitedList.end(), client.getNickname());
		_invitedList.erase(it);
	}
	for(vector<int>::iterator it = _clientFd.begin(); it != _clientFd.end(); it++)
	{
		if (*it == client.getFd())
		{
			 _clientFd.erase(it);
			 return;
		}
	}
}

bool	Channel::verifPassord(Client &client)
{
	if (client.getTokens().size() > 2)
	{
	 	if (_password.compare(client.getTokens()[2]) == 0)
			return (1);
	}
	client.setReply(ERR_BADCHANNELKEY(client.getNickname(), _name));
	return (0);
}

void	Channel::addOp(Client &client)
{
	_opList[client.getNickname()] = client;
}

void	Channel::removeOp(Client &client)
{
	_opList.erase(client.getNickname());
}

bool	Channel::isOp(Client &client)
{
	if (_opList.count(client.getNickname()))
		return (1);
	return (0);
}