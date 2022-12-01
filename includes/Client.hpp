#pragma		once

#include	"../includes/Utils.hpp"

class Client
{
private:
	int							_clientFd;
	struct sockaddr_in			_clientAddr;
	std::string					_nickname;
	int							_isAuth;
	std::string					_replyBuff;
	std::vector<std::string>	_tokens;

public:
	char						buff[BUFF_SIZE];
	std::string					appendBuff;
	Client(void);
	~Client();
	
	void						setFd(int _clientFd);
	void						setAdress(struct sockaddr_in clientAddr);
	void						setNickname(std::string nickname);
	void						setIsAuth(int auth);
	void						setReply(std::string replyBuff);

	const std::string			getNickname(void);
	int							getAuth(void);
	int							getFd(void);
	std::string					getReply(void);
	std::vector<std::string>	getTokens(void);

	void						clearReply(void);
	void						tokenize(std::string buff);
	void						clearTokens(void);
};
