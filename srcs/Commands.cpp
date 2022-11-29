#include	"../includes/Commands.hpp"

/*---------------Constructor/Destructor--------------*/
Commands::Commands()
{
	_commandMap["NICK"] = &Commands::nick;
}
Commands::~Commands()
{}
/*---------------------Setters-----------------------*/

/*----------------------Getters---------------------*/

/*-----------------MemberFunctions------------------*/
void	Commands::nick()
{
	std::cout << "\n[test]\n";
}
void Commands::execCommand(std::string s)
{
	_commandMap[s];
}