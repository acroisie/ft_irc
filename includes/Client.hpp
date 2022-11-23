#pragma once

#include "Utils.hpp"

class Client
{
	private:
		int			_fd;
		std::string	_nickName;
		std::string	_ClientName;

	public:
		Client();
		~Client();
		const int			&getFd();
		const std::string	&getNickName();
		const std::string 	&getClientName();
		void				setNickName(std::string s);
		void				setClientName(std::string s);
};