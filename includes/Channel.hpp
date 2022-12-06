#pragma 	once

#include	"Utils.hpp"
#include	<vector>
#include	"Client.hpp"

class Channel
{
	private:
		std::string			_name;
		std::string			_topic;
		std::vector<int>	_clientList;

	public:
		Channel(Client &client);
		~Channel();

		std::vector<int>	getClientList(void);
		std::string			getTopic(void);
		std::string			getName(void);

		void				setTopic(std::string topic);
		void				setClientList(int clientFd);
};