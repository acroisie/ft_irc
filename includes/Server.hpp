#pragma		once

<<<<<<< HEAD
#include	"Utils.hpp"

class Server
{
	private:
		const std::string			_port;
		const std::string			_password;
		struct sockaddr_in			_address;
		int							_serverFd;
		int							_opt;
		int							_newSocket;
		struct fd_set				_clientFds;
		struct fd_set				_readFds;
		struct fd_set				_writeFds;
		struct timeval				_timeout;
		char						_buffer[512];
		std::vector<std::string>	_tokens;


	public:
		Server(const std::string& port, const std::string& password);
		~Server();

		int		getServerFd(void);
		int		getSocketOpt(void);
		void	socketInit(void);
		void	handleMessage(int	currentFd);
		void	handleNewConnexion(void);
		void	replyToClient(int currentFd);
		void	start(void);
		void	parseCommand(int currentFd);

};
=======
#include	"../includes/Utils.hpp"
#include	"../includes/Client.hpp"

class Client;

class Server
{
private:
	std::string				_port;
	std::string				_password;
	int						_serverFd;
	struct fd_set			_clientFds;
	struct fd_set			_readFds;
	struct fd_set			_writeFds;
	struct sockaddr_in		_address;
	int						_addrLen;
	struct timeval			_timeout;
	std::map<int, Client>	_clientMap;

public:
	Server(const std::string& port, const std::string& password);
	~Server();

	void	start(void);
	void	socketInit(void);
	void	acceptNewClient(void);
};
>>>>>>> lNW/master
