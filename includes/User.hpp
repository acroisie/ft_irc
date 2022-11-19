#pragma once

#include "Utils.hpp"

class User
{
	private:
		std::string	_nickName;
		std::string	_userName;
	public:
		User();
		~User();
		const std::string	&getNickName();
		const std::string 	&getUserName();
		void				setNickName(std::string s);
		void				setUserName(std::string s);
};