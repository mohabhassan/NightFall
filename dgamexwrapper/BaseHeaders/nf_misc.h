#pragma once

//trimmed down (and extended) version of the original misc funcs by Razorapid


#define MD5_STR_SIZE 33

bool md5File(const char* file_name, char md5Str[MD5_STR_SIZE]);//MD5_DIGEST_SIZE*2+1

bool validateIP(const char* ip);

/* GameMessage Types */
#define HUD_MESSAGE_YELLOW			0x01
#define HUD_MESSAGE_WHITE			0x03
#define HUD_MESSAGE_CHAT_WHITE		0x02
#define HUD_MESSAGE_CHAT_RED		0x04

void SendGameMessage(int clientNum, char message_type, const char* text, ...);


#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		8192
#define	BIG_INFO_VALUE		8192
char* Info_ValueForKey(const char* s, const char* key);

bool CheckFPSSkin(char* userinfo);
bool CheckCommentSlashesInName(char* name);
