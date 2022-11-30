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

void	Commands::clearTokens(void)
{
	_tokens.clear();
}

void	Commands::execCommand(void)
{
	std::map<std::string, void (Commands::*)()>::iterator it = _commandMap.find(_tokens[0]);
	if (it != _commandMap.end())
		(this->*(it->second))();
}

void	Commands::tokenize(char *buff)
{
	std::cout << "[" << buff << "]\n";
	std::cout << strlen(buff);
	buff[strlen(buff) - 2] = '\0';
    std::string tempStr;
    std::stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
        _tokens.push_back(tempStr);
	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
       std::cout << std::endl << "{" << *it << "}\n"; // To delete
}

void	Commands::cap(void)
{
	std::cout << "\n|TEST cap|\n";
}

void	Commands::user(void)
{
	std::cout << "\n|TEST user|\n";
}

void	Commands::pass(void)
{
	std::cout << "|TEST pass|";
}
void	Commands::nick(void)
{
	_clientMap[currentFd].setNickname(_tokens[1]);
	std::cout << "nick: " << _clientMap[currentFd].getNickname() << '$' << std::endl; //to del
	std::string	test = ERR_WRONGPASSWORD(_clientMap[currentFd].getNickname());
	std::cout << test << std::endl; // degager
	//send(currentFd, test.c_str(), test.size(), 0);
}

char	*Commands::getReply(void)
{
	return(_replyBuff);
}