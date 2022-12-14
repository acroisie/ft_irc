#pragma		once

#include	<iostream>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<fcntl.h>
#include	<sys/select.h>
#include	<map>
#include	<netdb.h>
#include	<vector>
#include	<sstream>
#include	<unistd.h>
#include	<vector>
#include 	<string>

#define 	MAX_CONNECTIONS 42
#define 	BUFF_SIZE 4096

#define		RPL_WELCOME(client)										"001 " + client + " :Welcome " + client + " to the ft_irc network\r\n"
#define 	RPL_TOPIC(client, channel, topic)						"332 " + client + " " + channel + " :" + topic + "\r\n"
#define		RPL_NOTOPIC(client, channel)							"331 " + client + " " + channel + " :No topic is set\r\n"
#define		RPL_JOIN(client, channel)								":" + client + " JOIN :" + channel + "\r\n"
#define		RPL_NAMEPLY(client, symbol, channel, membershipList)	"353 " + client + " " + symbol + " " + channel + " :" + membershipList + "\r\n"
#define		RPL_ENDOFNAME(client, channel)							"366 " + client + " " + channel + " :End of /NAMES list\r\n"
#define		RPL_PING(token)											"PONG " + token + "\r\n"
#define		RPL_PRIVMSG(client, target, msg)						":" + client + " PRIVMSG " + target + " :" + msg + "\r\n"
#define		RPL_KICK(channel, client, comment)						":" channel + client + "*(" + "," client ")" + "[" + comment + "]\r\n"
#define		RPL_NICK(client, newnick)										":" + client + " NICK " + newnick +  "\r\n"

#define		ERR_WRONGPASSWORD(client)								"464 " + client + " :Password incorrect\r\n"
#define		ERR_BADCHANMASK(channel)								"476 " + channel + " : Bad Channel Mask\r\n"
#define		ERR_NOSUCHNICK(client, nickname)						"401 " + client + " " + nickname + " :No such nick/channel\r\n"
#define		ERR_NOTONCHANNEL(client, channel)						"442 " + client + " " +  channel +  "You're not on that channel\r\n"
#define		ERR_BANNEDFROMCHAN(client, channel)						"474 " + client + " " + channel + " :Cannot join channel (+b)\r\n"
