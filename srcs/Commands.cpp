#include	"../includes/Commands.hpp"

/*---------------Constructor/Destructor--------------*/
Commands::Commands()
{
	_commandMap["NICK"] = &Commands::nick;
	_commandMap["PASS"] = &Commands::pass;
	_commandMap["CAP"] = &Commands::cap;
	_commandMap["USER"] = &Commands::user;
	_commandMap["JOIN"] = &Commands::user;
	_commandMap["QUIT"] = &Commands::user;
}

Commands::~Commands(){}

/*---------------------Setters-----------------------*/

void	Commands::setPassword(std::string pass){_password = pass;}

/*----------------------Getters---------------------*/


/*-----------------MemberFunctions------------------*/

void	Commands::execCommand(Client &client)
{
	std::map<std::string, void (Commands::*)(Client &)>::iterator it = _commandMap.find(client.getTokens()[0]);
	if (it != _commandMap.end())
		(this->*(it->second))(client);
}

void	Commands::nick(Client &client)
{
	client.setNickname(client.getTokens()[1]);
	if(!client.getAuth())
	{
		client.setIsAuth(-1);
		client.setReply(ERR_WRONGPASSWORD(client.getNickname()));	
	}
	else
		client.setReply(RPL_WELCOME(client.getNickname()));
}

void	Commands::pass(Client &client)
{
	std::cout << client.getTokens()[0];
	if (client.getTokens()[1] == _password)
		client.setIsAuth(1);
}

void	Commands::cap(Client &client)
{
	(void)client;
}

void	Commands::user(Client &client)
{
	(void)client;
}

void	Commands::join(Client &client)
{
}

void	Commands::quit(Client &client)
{
	(void)client;
	// close(client.getFd());
}
