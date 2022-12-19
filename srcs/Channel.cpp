#include	"../includes/Channel.hpp"
using 		namespace std;

/*---------------Constructor/Destructor--------------*/

Channel::Channel(){}
Channel::~Channel(){}

/*---------------------Setters-----------------------*/

//void				Channel::setClientList(Client &client){_clientList.push_back(client);}
void				Channel::setTopic(string topic){_topic = topic;}
void				Channel::setSymbol(string symbol){_symbol = symbol;}
void				Channel::setName(string name){_name = name;}
void				Channel::setPassword(string password){_password = password;}
void				Channel::setMode(string mode){_mode = mode;}
void				Channel::setNameFd(string name, int fd){_nameFd[name] = fd;}
void				Channel::setFd(int fd)
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

/*----------------------Getters---------------------*/

//vector<Client>	Channel::getClientList(void){return (_clientList);}
string				Channel::getTopic(void){return (_topic);}
string				Channel::getSymbol(void){return (_symbol);}
string				Channel::getName(void){return (_name);}
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
	for(vector<int>::iterator it = _clientFd.begin(); it != _clientFd.end(); it++)
	{
		if (*it == client.getFd())
		{
			 _clientFd.erase(it);
			 return ;
		}
	}
}