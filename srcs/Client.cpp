#include	"../includes/Client.hpp"

/*---------------Constructor/Destructor--------------*/

Client::Client(void) : _isAuth(0){}
Client::~Client(){}

/*---------------------Setters-----------------------*/

void	Client::setNickname(std::string nickname){(void)_isAuth;_nickname =  nickname;}
void	Client::setIsAuth(void){_isAuth = 1;}
void	Client::setFd(int clientFd){_clientFd =  clientFd;}
void	Client::setAdress(struct sockaddr_in clientAddr){_clientAddr =  clientAddr;}

/*----------------------Getters---------------------*/

const std::string	Client::getNickname(void){return (_nickname);}
bool				Client::getAuth(void){return (_isAuth);}
int					Client::getFd(void){return (_clientFd);}
/*-----------------MemberFunctions------------------*/