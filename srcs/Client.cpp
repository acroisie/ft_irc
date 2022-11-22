#include "../includes/Client.hpp"

Client::Client()
{
	std::cout << "Constructor Client Called\n";
}

Client::~Client()
{
	std::cout << " Destructor Client Called\n";
}

const std::string &Client::getNickName()
{
	return(this->_nickName);
}
const std::string &Client::getClientName()
{
	return(this->_ClientName);
}

void Client::setNickName(std::string s)
{
	this->_nickName = s;
}
void Client::setClientName(std::string s)
{
	this->_ClientName = s;
}