#include	"../includes/Commands.hpp"

/*---------------Constructor/Destructor--------------*/
Commands::Commands()
{
	_commandMap["NICK"] = &Commands::nick;
	_commandMap["PASS"] = &Commands::pass;
	_commandMap["CAP"] = &Commands::cap;
	_commandMap["USER"] = &Commands::user;
}

Commands::~Commands(){}
/*---------------------Setters-----------------------*/

/*----------------------Getters---------------------*/

/*-----------------MemberFunctions------------------*/

void	Commands::execCommand(void)
{
	std::map<std::string, void (Commands::*)()>::iterator it = _commandMap.find(_tokens[0]);
	if (it != _commandMap.end())
	{
		(this->*(it->second))();

	}
}

void	Commands::tokenize(char *buff)
{
	_tokens = splitString(buff, ' ');
	std::vector<std::string>::iterator it = _tokens.begin();
	std::cout << *it;
	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++)
	{
       std::cout << "{" << *it << "}\n";
    }
}

void	Commands::cap(void)
{
	std::cout << "\n|TESTcap|\n";
}

void	Commands::user(void)
{
	std::cout << "\n|TESTuser|\n";
}

void	Commands::pass(void)
{
	std::cout << "\n|TESTpass|\n";
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