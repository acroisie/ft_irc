#include	"../includes/Utils.hpp"

std::vector<std::string> splitString(std::string input, char separator)
{
    size_t						pos;
    std::vector<std::string>	token;

    while (!input.empty())
	{
        pos = input.find(separator);
        if (pos == std::string::npos)
		{
            token.push_back(input);
            break;
        }
        token.push_back(input.substr(0, pos));
        input = input.substr(pos + 1);
    }
    return (token);
}