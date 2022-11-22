#pragma		once

#include	"Utils.hpp"
#include	"User.hpp"
class User;
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
		std::map<int, User *>		_userTab;

	
	public:
		Server(const std::string& port, const std::string& password);
		~Server();

		int		getServerFd(void);
		int		getSocketOpt(void);
		void	socketInit(void);
		void	handleMessage(int	currentFd);
		void	start(void);
		void	addUserInTab(int fd);
};
