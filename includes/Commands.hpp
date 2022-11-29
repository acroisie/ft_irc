#pragma once

#include "Utils.hpp"

class Commands
{
	private:
		std::map<std::string, void (Commands::*)() > _commandMap;
	public:
		Commands();
		~Commands();
		void	execCommand(std::string s);
		void	nick();
};