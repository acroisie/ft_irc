#include	"../includes/Server.hpp"

Server::Server(const std::string& port, const std::string& password)
:_port(port), _password(password){}

Server::~Server(){}