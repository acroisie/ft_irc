#include	"../includes/Channel.hpp"

/*---------------Constructor/Destructor--------------*/

Channel::Channel(){}
Channel::~Channel(){}

/*---------------------Setters-----------------------*/

//void				Channel::setClientList(Client &client){_clientList.push_back(client);}
void				Channel::setTopic(std::string topic){_topic = topic;}
void				Channel::setSymbol(std::string symbol){_symbol = symbol;}
void				Channel::setName(std::string name){_name = name;}
void				Channel::setPassword(std::string password){_password = password;}
void				Channel::setFd(int fd){_clientFd.push_back(fd);}
void				Channel::setNameFd(std::string name, int fd){_nameFd[name] = fd;}

/*----------------------Getters---------------------*/

//std::vector<Client>	Channel::getClientList(void){return (_clientList);}
std::string			Channel::getTopic(void){return (_topic);}
std::string			Channel::getSymbol(void){return (_symbol);}
std::string			Channel::getName(void){return (_name);}
std::vector<int>	&Channel::getFdVector(void){return (_clientFd);}
int					Channel::getNameFd(std::string name){return (_nameFd[name]);}

/*-----------------MemberFunctions------------------*/
