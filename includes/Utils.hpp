#pragma		once

// #include	"../includes/Server.hpp"
// #include	"../includes/Client.hpp"

#include	<iostream>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<fcntl.h>
#include	<sys/select.h>
#include	<map>
#include	<netdb.h>
#include	<vector>

#define 	MAX_CONNECTIONS 42
#define 	BUFF_SIZE 1024

std::vector<std::string> splitString(std::string input, char separator);