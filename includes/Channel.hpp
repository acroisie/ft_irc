#pragma 	once

#include	"Utils.hpp"
#include	<vector>
#include	"Client.hpp"

class Channel
{
	private:
		std::string			_name;
		std::vector<int>	_clientList;
	public:
		Channel(Client &client);
		~Channel();

		std::vector<int>	getClientList(void);
		
		void				setClientList(int clientFd);
};