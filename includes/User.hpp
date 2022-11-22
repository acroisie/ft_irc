#pragma once

#include "Utils.hpp"

class Client
{
	private:
		std::string	_nickName;
		std::string	_ClientName;
	public:
		Client();
		~Client();
		const std::string	&getNickName();
		const std::string 	&getClientName();
		void				setNickName(std::string s);
		void				setClientName(std::string s);
};