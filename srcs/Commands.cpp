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

void	Commands::execCommand(Client &client)
{
	std::map<std::string, void (Commands::*)(Client &)>::iterator it = _commandMap.find(_tokens[0]);
	if (it != _commandMap.end())
		(this->*(it->second))(client);
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
// 	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
//     	std::cout << std::endl << "{" << *it << "}"; // To delete
}

void	Commands::cap(Client &client)
{
	std::cout << "\n|TEST cap|\n";
	(void)client;
}

void	Commands::user(Client &client)
{
	std::cout << "\n|TEST user|\n";
	(void)client;
}

void	Commands::pass(Client &client)
{
	std::cout << "\n|TEST pass|\n";
	(void)client;
}
void	Commands::nick(Client &client)
{
// 	std::cout << "*it: " << *it << std::endl; //to del
// 	std::cout << "*it++: " << *it++ << std::endl; //to del
// 	std::string str;
// 	str = *it;
	client.setNickname(_tokens[1]);
	std::cout << "nick: " << client.getNickname() << '$' << std::endl; //to del
	// std::string	test = ERR_WRONGPASSWORD(_clientMap[currentFd].getNickname());
	// std::cout << test << std::endl; // degager
	// send(currentFd, test.c_str(), test.size(), 0);
}