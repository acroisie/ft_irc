#pragma once

#include "Client.hpp"
#include "Utils.hpp"

class Commands
{
	private:
		std::map<std::string, void (Commands::*)(Client &)>	_commandMap;
		std::string											_password;

	public:
		Commands();
		~Commands();

		void		setPassword(std::string pass);

		void		execCommand(Client &client);
		void		nick(Client &client);
		void		pass(Client &client);
		void		user(Client &client);
		void		cap(Client &client);
		void		join(Client &client);
		void		quit(Client &client);
};
