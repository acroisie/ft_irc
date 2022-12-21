#include	"../includes/Client.hpp"
using		namespace std;

/*---------------Constructor/Destructor--------------*/

Client::Client(void):   _isAuth(0)
{
	_nickname = "DefaultNickname";
	bzero(_checkAuth, 4);
	
}
Client::~Client(){}

/*---------------------Setters-----------------------*/

void					Client::setNickname(string nickname){(void)_isAuth;_nickname =  nickname;}
void					Client::setIsAuth(int auth){_isAuth = auth;}
void					Client::setIsOp(bool op){_isOp = op;}
void					Client::addClientFd(int clientFd){_clientFd = clientFd;}
void					Client::setAdress(struct sockaddr_in clientAddr){_clientAddr =  clientAddr;}
void					Client::setReply(string replyBuff){_replyBuff += replyBuff;};
void					Client::setPrefix(string prefix){_prefix = prefix;};
void					Client::setUsername(string username){_username = username;};
void					Client::setRealname(string realname){_realname = realname;};
void					Client::setCheckAuth(string flag)
{
	if (flag.compare("pass") == 0)
		_checkAuth[0] = 1;
	else if (flag.compare("nick") == 0)
		_checkAuth[1] = 1;
	else if (flag.compare("user") == 0)
		_checkAuth[2] = 1;
};
void					Client::unsetCheckAuth(string flag)
{
	if (flag.compare("pass") == 0)
		_checkAuth[0] = 0;
	else if (flag.compare("nick") == 0)
		_checkAuth[1] = 0;
	else if (flag.compare("user") == 0)
		_checkAuth[2] = 0;
};

/*----------------------Getters---------------------*/

const string			Client::getNickname(void){return (_nickname);}
const string			Client::getUsername(void){return (_username);}
int						Client::getAuth(void){return (_isAuth);}
bool                    Client::getIsOp(void){return (_isOp);}
int						Client::getFd(void){return (_clientFd);}
string					Client::getReply(void){return (_replyBuff);}
string					Client::getPrefix(void){return (_prefix);}
vector<string>	        &Client::getTokens(void){return (_tokens);}
int						Client::getCheckAuth(string flag)
{
	if (flag.compare("pass") == 0)
		return (_checkAuth[0]);
	else if (flag.compare("nick") == 0)
		return (_checkAuth[1]);
	else if (flag.compare("user") == 0)
		return(_checkAuth[2]);
	return (-1);
};

/*-----------------MemberFunctions------------------*/
bool					Client::authIsValid()
{
	if (_checkAuth[0] == 1 && _checkAuth[1] == 1  && _checkAuth[2] == 1)
		return (1);
	else
		return (0);
}
void                    Client::clearReply(void){_replyBuff.clear();}

void                    Client::tokenize(string buff)
{
    string tempStr;
    stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
    {
        _tokens.push_back(tempStr);
        tempStr.clear();
    }
 	for (vector<string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
        cout << "{" << *it << "}" << endl; // To delete
}

void                    Client::clearTokens(void){_tokens.clear();}