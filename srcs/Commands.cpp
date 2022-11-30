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

void	Commands::setPassword(std::string pass){_password = pass;}

/*----------------------Getters---------------------*/

std::string	Commands::getReply(void){return (_replyBuff);}

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
	buff[strlen(buff) - 2] = '\0';
    std::string tempStr;
    std::stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
        _tokens.push_back(tempStr);
 	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
     	std::cout << std::endl << "{" << *it << "}\n"; // To delete
}

void	Commands::cap(Client &client)
{
	(void)client;
}

void	Commands::user(Client &client)
{
	(void)client;
}

void	Commands::pass(Client &client)
{
	if (_tokens[1] == _password)
	{
		client.setIsAuth();
	}
	_replyBuff = ERR_WRONGPASSWORD(client.getNickname());
}
void	Commands::nick(Client &client)
{
	client.setNickname(_tokens[1]);
	std::cout << "nick: " << client.getNickname() << '$' << std::endl;
}
