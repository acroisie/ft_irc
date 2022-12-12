#pragma 	once

#include	"Utils.hpp"
#include	"Client.hpp"

class Channel
{
	private:
		std::string			_name;
		std::string			_topic;
		std::string			_symbol;
		std::vector<int>	_clientFd;

	public:
		Channel(Client &client);
		~Channel();

		std::string			getTopic(void);
		std::string			getName(void);
		std::string			getSymbol(void);
		std::vector<int>	&getFdVector(void);

		void				setTopic(std::string topic);
		void				setSymbol(std::string symbol);
		void				setFd(int fd);
};