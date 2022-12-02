#include	"../includes/Client.hpp"

/*---------------Constructor/Destructor--------------*/

Client::Client(void): _isAuth(0){}
Client::~Client(){}

/*---------------------Setters-----------------------*/

void						Client::setNickname(std::string nickname){(void)_isAuth;_nickname =  nickname;}
void						Client::setIsAuth(int auth){_isAuth = auth;}
void						Client::setFd(int clientFd){_clientFd =  clientFd;}
void						Client::setAdress(struct sockaddr_in clientAddr){_clientAddr =  clientAddr;}
void						Client::setReply(std::string replyBuff){_replyBuff = replyBuff;};

/*----------------------Getters---------------------*/

const std::string			Client::getNickname(void){return (_nickname);}
int							Client::getAuth(void){return (_isAuth);}
int							Client::getFd(void){return (_clientFd);}
std::string					Client::getReply(void){return (_replyBuff);}
std::vector<std::string>	Client::getTokens(void){return (_tokens);}

/*-----------------MemberFunctions------------------*/

void				Client::clearReply(void){_replyBuff.clear();}

void	Client::tokenize(std::string buff)
{
	// _appendBuff += _buffer;
	// bzero(_buffer, strlen(_buffer));
	// size_t	pos = 0;
	// std::cout << "\npos: " << (pos = _appendBuff.find("\r\n")) << std::endl;
	// std::cout << "\n_appendBuff: " << _appendBuff << std::endl;
	// if ((pos = _appendBuff.find("\r\n")) != std::string::npos)
	// {
	// size_t		pos;
    std::string tempStr;
    std::stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
	{
		// if ((pos = tempStr.find("\r\n")))
		// 	tempStr = tempStr.substr(0, pos);
		// if ((pos = tempStr.find("\n")))
		// 	tempStr = tempStr.substr(0, pos);
        _tokens.push_back(tempStr);
	}
 	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
     	std::cout << "{" << *it << "}" << std::endl; // To delete
}

void	Client::clearTokens(void){_tokens.clear();}