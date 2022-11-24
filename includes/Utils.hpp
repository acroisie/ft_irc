#pragma	once

#include	<iostream>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<errno.h>
#include	<stdlib.h>
#include	<sys/select.h>
#include	<sys/time.h>
#include	<sstream>
#include	<fcntl.h>
#include	<map>
#include	<unistd.h>
#include	<vector>
#include	<string>

#define 	MAX_CONNECTIONS 42

std::vector<std::string> splitString(std::string input, char separator);