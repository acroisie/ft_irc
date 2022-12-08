#pragma 	once

#include	"Utils.hpp"
#include	"Client.hpp"

class Channel
{
	private:
		std::string			_name;
		std::string			_topic;
		std::vector<Client>	_clientList;
		std::string			_symbol;
		std::vector<int>	_clientFd;

	public:
		Channel(Client &client);
		~Channel();

		std::vector<Client>	getClientList(void);
		std::string			getTopic(void);
		std::string			getName(void);
		std::string			getSymbol(void);
		std::vector<int>	getFdVector(void);

		void				setTopic(std::string topic);
		void				setSymbol(std::string symbol);
		void				setClientList(Client &client);
		void				setFd(int fd);

		std::string			membershipList(void);
};