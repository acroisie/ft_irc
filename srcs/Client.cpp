#include	"../includes/Client.hpp"
using		namespace std;

/*---------------Constructor/Destructor--------------*/

Client::Client(void):   _isAuth(0){_nickname = "DefaultNickname";}
Client::~Client(){}

/*---------------------Setters-----------------------*/

void					Client::setNickname(string nickname){(void)_isAuth;_nickname =  nickname;}
void					Client::setIsAuth(int auth){_isAuth = auth;}
void					Client::setIsOp(bool op){_isOp = op;}
void					Client::addClientFd(int clientFd){_clientFd = clientFd;}
void					Client::setAdress(struct sockaddr_in clientAddr){_clientAddr =  clientAddr;}
void					Client::setReply(string replyBuff){_replyBuff += replyBuff;};
void					Client::setPrefix(string prefix){_prefix = prefix;};
void					Client::setNickOk(bool i){_nickOk = i;};
void					Client::setUserOk(bool i){_userOk = i;};
void					Client::setUsername(string username){_username = username;};
void					Client::setRealname(string realname){_realname = realname;};

/*----------------------Getters---------------------*/

const string			Client::getNickname(void){return (_nickname);}
const string			Client::getUsername(void){return (_username);}
int						Client::getAuth(void){return (_isAuth);}
bool                    Client::getIsOp(void){return (_isOp);}
int						Client::getFd(void){return (_clientFd);}
string					Client::getReply(void){return (_replyBuff);}
string					Client::getPrefix(void){return (_prefix);}
vector<string>	        &Client::getTokens(void){return (_tokens);}
bool					Client::getUserOk(){return (_userOk);}
bool					Client::getNickOk(){return (_nickOk);}

/*-----------------MemberFunctions------------------*/

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