#include "../includes/User.hpp"

User::User()
{
	std::cout << "Constructor User Called\n";
}

User::~User()
{
	std::cout << " Destructor User Called\n";
}

const std::string &User::getNickName()
{
	return(this->_nickName);
}
const std::string &User::getUserName()
{
	return(this->_userName);
}

void User::setNickName(std::string s)
{
	this->_nickName = s;
}
void User::setUserName(std::string s)
{
	this->_userName = s;
}