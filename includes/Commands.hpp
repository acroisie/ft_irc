#pragma once

#include "Client.hpp"
#include "Utils.hpp"

class Commands
{
	private:
		std::vector<std::string>							_tokens;
		std::map<std::string, void (Commands::*)(Client &)>	_commandMap;
		std::string											_password;
		std::string											_replyBuff;	
		bool												_replyOn;								

	public:
		Commands();
		~Commands();

		void		setPassword(std::string pass);
		void		setReplyOn(int o);

		std::string	getReply(void);
		int			getReplyOn(void);

		void		tokenize(char *_buffer);
		void		clearTokens(void);
		void		execCommand(Client &client);
		void		nick(Client &client);
		void		pass(Client &client);
		void		user(Client &client);
		void		cap(Client &client);
		void		join(Client &client);
};
