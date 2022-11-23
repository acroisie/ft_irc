#include "../includes/Client.hpp"

Client::Client()
{
	std::cout << "Constructor Client Called\n";
}

Client::~Client()
{
	std::cout << " Destructor Client Called\n";
}

const int		 &Client::getFd()
{
	return(_fd);
}

const std::string &Client::getNickName()
{
	return(_nickName);
}
const std::string &Client::getClientName()
{
	return(_ClientName);
}

void Client::setNickName(std::string s)
{
	_nickName = s;
}
void Client::setClientName(std::string s)
{
	_ClientName = s;
}