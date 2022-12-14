#pragma 	once

#include	"Utils.hpp"
#include	"Client.hpp"

class Client;

class Channel
{
	private:
		std::string					_name;
		std::string					_password;
		std::string					_topic;
		std::string					_symbol;
		std::string					_mode;
		std::vector<int>			_clientFd;
		std::map<std::string, int>	_nameFd;
		std::map<std::string, int>	_bannedClientFd;
	public:
		Channel();
		~Channel();

		std::string			getTopic(void);
		std::string			getName(void);
		std::string			getSymbol(void);
		std::string			getMode(void);
		std::vector<int>	&getFdVector(void);
		int					getNameFd(std::string name);

		void				setTopic(std::string topic);
		void				setSymbol(std::string symbol);
		void				setName(std::string name);
		void				setMode(std::string mode);
		void				setPassword(std::string password);
		void				setNameFd(std::string name, int fd);
		void				setFd(int fd);

		bool				clientIsBanned(Client &client);
		bool				clientIsOnChan(Client &client);
};