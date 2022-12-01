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
	size_t		pos;
    std::string tempStr;
    std::stringstream strStream(buff);
    while (getline(strStream, tempStr, ' '))
	{
		if ((pos = tempStr.find("\r\n")))
			tempStr = tempStr.substr(0, pos);
		if ((pos = tempStr.find("\n")))
			tempStr = tempStr.substr(0, pos);
        _tokens.push_back(tempStr);
	}
 	for (std::vector<std::string>::iterator it = _tokens.begin(); it != _tokens.end(); it++) // To delete
     	std::cout << "{" << *it << "}" << std::endl; // To delete
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
		client.setIsAuth(1);
}

void	Commands::nick(Client &client)
{
	client.setNickname(_tokens[1]);
	if(!client.getAuth())
	{
		client.setIsAuth(-1);
		_replyBuff = ERR_WRONGPASSWORD(client.getNickname());	
	}
	else
		_replyBuff = RPL_WELCOME(client.getNickname());
}
