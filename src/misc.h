#pragma once
// Misc and custom user-written functions
// Added by Razorapid

#include "xtrace.h"

#include "dgamex86.h"

/* GameMessage Types */ 
#define HUD_MESSAGE_YELLOW			0x01
#define HUD_MESSAGE_WHITE			0x03
#define HUD_MESSAGE_CHAT_WHITE		0x02
#define HUD_MESSAGE_CHAT_RED		0x04


#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		8192
#define	BIG_INFO_VALUE		8192

extern void SendGameMessage(int clientNum, char message_type, const char *text, ... );
extern void BroadcastGameMessage(int maxClients, char message_type, const char *text, ... );
extern char *Info_ValueForKey(const char *s, const char *key);
//extern void Info_SetValueForKey( char *s, const char *key, const char *value );//not working
//extern void Info_RemoveKey( char *s, const char *key );//not working
extern void add_log(const char *level, const char *fmt, ...);
extern void *MyMallocImpl( int size, const char * function, const char * file, int line );
extern void MyFreeImpl( void *ptr, const char * function, const char * file, int line );
extern void CreateRandomText(int length, char *returned_text);
char* mystrndup (const char *s, size_t len);
char* substring(const char* str, size_t begin, size_t len);
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
char * make_message(const char *fmt, ...);
void getDateTimeInto(char *buf);
int msleep(unsigned long milisec);
unsigned long clockMsec();
int parseint(const char *str, int mustbefullmatch, int errorvalue);

bool validateIP(const char *ip);

bool md5File(const char* file_name, char md5Str[MD5_DIGEST_SIZE * 2 + 1]);

#ifndef _WIN32
void initsighandlers();
void resetsighandlers();
void sighandler(int sig, siginfo_t *info, void *secret);
#endif

#ifndef __FUNCTION__
#define __FUNCTION__ const char * function
#endif