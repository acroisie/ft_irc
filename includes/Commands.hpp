#pragma once

#include "Utils.hpp"

class Commands
{
	private:
		std::vector<std::string>					_tokens;
		std::map<std::string, void (Commands::*)()>	_commandMap;
		char										_replyBuff[BUFF_SIZE];									

	public:
		Commands();
		~Commands();

		void	tokenize(char *_buffer);
		char	*getReply(void);
		void	clearTokens(void);
		void	execCommand(void);
		void	nick(void);
		void	pass(void);
		void	user(void);
		void	cap(void);
		void	join(void);
};
