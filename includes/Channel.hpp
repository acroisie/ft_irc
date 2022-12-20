#pragma 	once

#include	"Utils.hpp"
#include	"Client.hpp"
using		namespace std;

class Client;

class Channel
{
	private:
		string				_name;
		string				_password;
		string				_topic;
		string				_symbol;
		string				_modeI;
		string				_modeK;
		vector<int>			_clientFd;
		map<string, int>	_nameFd;
		map<string, int>	_bannedClientFd;
		vector<string>		_invitedList;

	public:
		Channel();
		~Channel();

		string				getTopic(void);
		string				getName(void);
		string				getSymbol(void);
		string				getModeI(void);
		string				getModeK(void);
		vector<int>			&getFdVector(void);
		vector<string>		&getInvitedList(void);
		int					getNameFd(string name);
		string				getPassword(void);

		void				setTopic(string topic);
		void				setSymbol(string symbol);
		void				setName(string name);
		void				setModeI(string mode);
		void				unsetModeI(void);
		void				setModeK(string mode);
		void				setInvited(string name);
		void				setPassword(string password);
		void				setNameFd(string name, int fd);
		void				addClientFd(int fd);

		bool				clientIsBanned(Client &client);
		bool				clientIsOnChan(Client &client);
		void				eraseClient(Client &client);
		bool				verifPassord(Client &client);
};	