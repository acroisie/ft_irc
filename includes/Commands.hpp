#pragma once

#include "Client.hpp"
#include "Utils.hpp"

class Commands
{
	private:
		std::vector<std::string>					_tokens;
		std::map<std::string, void (Commands::*)(Client &)>	_commandMap;
		char										_replyBuff[BUFF_SIZE];									

	public:
		Commands();
		~Commands();

		void	tokenize(char *_buffer);
		char	*getReply(void);
		void	clearTokens(void);
		void	execCommand(Client &client);
		void	nick(Client &client);
		void	pass(Client &client);
		void	user(Client &client);
		void	cap(Client &client);
		void	join(Client &client);
};
