#pragma once

#include "Utils.hpp"

class Commands
{
private:
	std::vector<std::string>	_tokens;

public:
	Commands(/* args */);
	~Commands();

	void	tokenize(char *_buffer);
	void	nick(void);
};
