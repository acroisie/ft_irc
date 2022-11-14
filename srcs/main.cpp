#include	"../includes/Server.hpp"

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 3)
		{
			//verif int max etc
			throw std::invalid_argument(("Invalid args ./ircserv <port> <password>"));
		}
		Server(argv[1], argv[2]); //un truc dans le genre
		return (0);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}