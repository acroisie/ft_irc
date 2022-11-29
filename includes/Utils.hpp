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

#define		RPL_WELCOME(client)				"001 " + client + " :Welcome " + client + " to the ft_irc network\r\n"

#define		ERR_WRONGPASSWORD(client)		"464 " + client + " :Password incorrect\r\n"

std::vector<std::string>					splitString(std::string input, char separator);