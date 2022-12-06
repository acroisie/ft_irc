#include	"../includes/Client.hpp"

/*---------------Constructor/Destructor--------------*/

Client::Client(void): _isAuth(0){}
Client::~Client(){}

/*---------------------Setters-----------------------*/

void						Client::setNickname(std::string nickname){(void)_isAuth;_nickname =  nickname;}
void						Client::setIsAuth(int auth){_isAuth = auth;}
void						Client::setIsOp(bool op){_isOp = op;}
void						Client::setFd(int clientFd){_clientFd =  clientFd;}
void						Client::setAdress(struct sockaddr_in clientAddr){_clientAddr =  clientAddr;}
void						Client::setReply(std::string replyBuff){_replyBuff = replyBuff;};
void						Client::setPrefix(std::string prefix){_prefix = prefix;};
void						Client::setUsername(std::string username){_username = username;};
void						Client::setRealname(std::string realname){_realname = realname;};

/*----------------------Getters---------------------*/

const std::string			Client::getNickname(void){return (_nickname);}
int							Client::getAuth(void){return (_isAuth);}
bool						Client::getIsOp(void){return (_isOp);}
int							Client::getFd(void){return (_clientFd);}
std::string					Client::getReply(void){return (_replyBuff);}
std::string					Client::getPrefix(void){return (_prefix);}
std::vector<std::string>	Client::getTokens(void){return (_tokens);}

/*-----------------MemberFunctions------------------*/

void				Client::clearReply(void){_replyBuff.clear();}

void	Client::tokenize(std::string buff)
{
    std::string tempStr;
    std::stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
        _tokens.push_back(tempStr);

 	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
     	std::cout << "{" << *it << "}" << std::endl; // To delete
}

void	Client::clearTokens(void){_tokens.clear();}