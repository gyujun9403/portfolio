#ifndef __DEFINES_HPP__
#define __DEFINES_HPP__

#include <vector>
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
#include <unistd.h>
using namespace std;

#define SUCCESS 1
#define SERVERDOWN 0
#define FALSE -1
#define BUFFERSIZE 512
#define SERVERNAME "ircserv"

// Reply Code
#define RPL_WELCOME "001"
#define RPL_NAMREPLY "353"
#define RPL_ENDOFNAMES "366"
#define RPL_JOIN "JOIN"
#define RPL_NICK "NICK"
#define RPL_PART "PART"
#define RPL_MODE "MODE"
#define RPL_KICK "KICK"
#define RPL_PRIVMSG "PRIVMSG"
#define RPL_QUIT "QUIT"
#define RPL_NOTICE "NOTICE"

// Error code
#define ERR_NOSUCHNICK "401"
#define ERR_NOSUCHCHANNEL "403"
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_ERRONEOUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_USERNOTINCHANNEL "441"
#define ERR_NOTONCHANNEL "442"
#define ERR_USERONCHANNEL "443"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTERED "462"
#define ERR_PASSWDMISMATCH "464"
#define ERR_CHANNELISFULL "471"
#define ERR_BADCHANNELKEY "475"
#define ERR_CHANOPRIVSNEEDED "482"
#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_WRONGPROTOCOL "984"
#define ERR_TOOMANYPARAM "985"
#define ERR_NOTCONNECTED "986"
#define ERR_ALREADYCONNECTED "987"

#endif