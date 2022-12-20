#pragma		once

#include	"../includes/Utils.hpp"
using		namespace std;

class Client
{
private:
	int						_clientFd;
	struct sockaddr_in		_clientAddr;
	string					_nickname;
	int						_isAuth;
	bool					_isOp;
	string					_prefix;
	string					_replyBuff;
	vector<string>			_tokens;
	string					_username;
	string					_realname;

public:
	Client(void);
	~Client();
	
	string					appendBuff;
	
	void					addClientFd(int _clientFd);
	void					setAdress(struct sockaddr_in clientAddr);
	void					setNickname(string nickname);
	void					setIsAuth(int auth);
	void					setIsOp(bool op);
	void					setPrefix(string prefix);
	void					setReply(string replyBuff);
	void					setUsername(string replyBuff);
	void					setRealname(string replyBuff);

	const string			getNickname(void);
	bool					getIsOp(void);
	int						getAuth(void);
	int						getFd(void);
	string					getReply(void);
	string					getPrefix(void);
	vector<string>			&getTokens(void);

	void					clearReply(void);
	void					tokenize(string buff);
	void					clearTokens(void);
};
