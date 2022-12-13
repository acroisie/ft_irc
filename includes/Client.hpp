#pragma		once

#include	"../includes/Utils.hpp"

class Client
{
private:
	int							_clientFd;
	struct sockaddr_in			_clientAddr;
	std::string					_nickname;
	int							_isAuth;
	bool						_isOp;
	std::string					_prefix;
	std::string					_replyBuff;
	std::vector<std::string>	_tokens;
	std::string					_username;
	std::string					_realname;

public:
	std::string					appendBuff;
	Client(void);
	~Client();
	
	void						setFd(int _clientFd);
	void						setAdress(struct sockaddr_in clientAddr);
	void						setNickname(std::string nickname);
	void						setIsAuth(int auth);
	void						setIsOp(bool op);
	void						setPrefix(std::string prefix);
	void						setReply(std::string replyBuff);
	void						setUsername(std::string replyBuff);
	void						setRealname(std::string replyBuff);

	const std::string			getNickname(void);
	bool						getIsOp(void);
	int							getAuth(void);
	int							getFd(void);
	std::string					getReply(void);
	std::string					getPrefix(void);
	std::vector<std::string>	&getTokens(void);

	void						clearReply(void);
	void						tokenize(std::string buff);
	void						clearTokens(void);
};
