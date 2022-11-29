#pragma once

#include "Utils.hpp"

class Commands
{
	private:
		std::vector<std::string>					_tokens;
		std::map<std::string, void (Commands::*)()>	_commandMap;

	public:
		Commands();
		~Commands();

		void	tokenize(char *_buffer);
		void	execCommand(void);
		void	nick(void);
		void	pass(void);
		void	user(void);
		void	cap(void);
		void	join(void);
};
