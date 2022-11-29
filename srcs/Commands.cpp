#include	"../includes/Commands.hpp"

/*---------------Constructor/Destructor--------------*/
Commands::Commands()
{
	_commandMap["NICK"] = &Commands::nick;
}

Commands::~Commands(){}
/*---------------------Setters-----------------------*/

/*----------------------Getters---------------------*/

/*-----------------MemberFunctions------------------*/

void	Commands::execCommand(std::string str)
{
	std::map<std::string, void (Commands::*)()>::iterator it = _commandMap.find(str);
	(this->*(it->second))();
}

void	Commands::tokenize(char *buff)
{
	_tokens = splitString(buff, ' ');
	std::vector<std::string>::iterator it = _tokens.begin();
	std::cout << *it;
}

void	Commands::nick(void)
{
	std::cout << "\n|TESTnick|\n";
	//std::cout << "*it: " << *it << std::endl; //to del
	//std::cout << "*it++: " << *it++ << std::endl; //to del
	//std::string str;
	//str = *it;
	//str.erase(str.size() - 1);
	//str.erase(str.size() - 1);
	//_clientMap[currentFd].setNickname(str);
	//std::cout << "nick: " << _clientMap[currentFd].getNickname() << '$' << std::endl; //to del
	//std::string	test = ERR_WRONGPASSWORD(_clientMap[currentFd].getNickname());
	//std::cout << test << std::endl; // degager
	//send(currentFd, test.c_str(), test.size(), 0);
}