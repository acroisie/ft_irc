#pragma		once

#include	"../includes/Utils.hpp"
#include	"../includes/Client.hpp"
#include	"../includes/Channel.hpp"

class Client;

class Server
{
private:
	std::string											_port;
	std::string											_password;
	int													_serverFd;
	int													_opt;
	struct fd_set										_clientFds;
	struct fd_set										_readFds;
	struct fd_set										_writeFds;
	struct sockaddr_in									_address;
	int													_addrLen;
	struct timeval										_timeout;
	std::vector<std::string>							_commandRecv;
	std::map<int, Client>								_clientMap;
	std::map<int, void *>								_serverMap;
	std::map<std::string, Channel *>					_channelMap;
	std::map<std::string, void (Server::*)(Client &)>	_commandMap;
	std::string											_appendBuff;
	char												_buffer[BUFF_SIZE];

public:
	Server(const std::string& port, const std::string& password);
	~Server();

	void		start(void);
	void		socketInit(void);
	void		acceptNewClient(void);
	void		handleMsg(int currentFd);
	void		execCommand(Client &client);
	void		connectionLost(int currentFd);
	void		replyJoin(Client &client, Channel *channel);
	
	void		nick(Client &client);
	void		pass(Client &client);
	void		user(Client &client);
	void		cap(Client &client);
	void		join(Client &client);
	void		quit(Client &client);
	void		ping(Client &client);
	void		privMsg(Client &client);
	void		notice(Client &client);
	void		notice(Client &client, std::string chlName, std::string msg);
	void		mode(Client &client);
	void		topic(Client &client);
	void		kick(Client &client);
	void		part(Client &client);
	void		invite(Client &client);
	
	std::string	membershipList(Channel *channel);
	bool		nickAlreadyUse(Client &client);
	int			searchByNick(std::string name);
};