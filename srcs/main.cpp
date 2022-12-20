#include	"../includes/Server.hpp"
using		namespace std;

int	main(int argc, char** argv)
{
	try
	{
		if (argc != 3)
			throw invalid_argument(("Invalid args ./ircserv <port> <password>"));
		for (int i = 0; argv[1][i]; i++)
		{
			if (isalpha(argv[1][i]))
				throw invalid_argument(("Invalid args ./ircserv <port> <password>"));		
		}
		Server irc(argv[1], argv[2]);
		irc.start();
		return (0);
	}
	catch(const exception& e)
	{
		cerr << strerror(errno) << ": " << e.what() << endl;
		return (1);
	}
}

// /server add irc localhost/4242 -password=test