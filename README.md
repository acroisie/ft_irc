# ft_irc

Here is the ft_irc project wroted by [Luthernmr](https://github.com/Luthernmr) and I.

The goal of this project is to achieve a basic irc server in C++.

The rules:

* Manage multiple connections without fork
* Use poll() or equivalent (we use select()) to manage multiple clients interaction
* Set socket to non-blocking mode
* Authentify by nickname and password
* Manage channel gestion
* Get operator status/commands

You want to play with it? Start a beautifull shell and type > Make && ./ircserv <port> <password>
