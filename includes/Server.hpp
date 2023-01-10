#pragma		once

#include	"../includes/Utils.hpp"
#include	"../includes/Client.hpp"
#include	"../includes/Channel.hpp"
using		namespace std;

class Client;

class Server
{
private:
	string					_port;
	string					_password;
	int						_serverFd;
	int						_opt;
	struct fd_set			_clientFds;
	struct fd_set			_readFds;
	struct fd_set			_writeFds;
	struct sockaddr_in		_address;
	int						_addrLen;
	struct timeval			_timeout;
	vector<string>			_commandRecv;
	map<int, Client>		_clientMap;
	map<string, Channel *>	_channelMap;
	map<string, void \
	(Server::*)(Client &)>	_commandMap;
	string					_appendBuff;
	char					_buffer[BUFF_SIZE];

public:
	Server(const string& port, const string& password);
	~Server();
	static bool				running;
	void					start(void);
	void					socketInit(void);
	void					acceptNewClient(void);
	void					handleMsg(int currentFd);
	void					execCommand(Client &client);
	void					connectionLost(int currentFd);
	void					replyJoin(Client &client, Channel *channel);
	
	void					nick(Client &client);
	void					pass(Client &client);
	void					user(Client &client);
	void					cap(Client &client);
	void					join(Client &client);
	void					quit(Client &client);
	void					ping(Client &client);
	void					privMsg(Client &client);
	void					notice(Client &client);
	void					notice(Client &client, string chlName, string msg);
	void					mode(Client &client);
	void					topic(Client &client);
	void					kick(Client &client);
	void					part(Client &client);
	void					invite(Client &client);
	
	string					membershipList(Channel *channel);
	bool					nickAlreadyUse(Client &client);
	int						searchByNick(string name);
	bool					modeCheck(string chlName, Client &client);
	void					notifAll(Client &client, string mode);
	int						segvGuard(Client &Client);
};