#pragma 	once

#include	"Utils.hpp"
#include	"Client.hpp"

class Channel
{
	private:
		std::string					_name;
		std::string					_topic;
		std::string					_symbol;
		std::vector<int>			_clientFd;
		std::map<std::string, int>	_nameFd;

	public:
		Channel();
		~Channel();

		std::string			getTopic(void);
		std::string			getName(void);
		std::string			getSymbol(void);
		std::vector<int>	&getFdVector(void);
		int					getNameFd(std::string name);

		void				setTopic(std::string topic);
		void				setSymbol(std::string symbol);
		void				setName(std::string name);
		void				setNameFd(std::string name, int fd);
		void				setFd(int fd);
};