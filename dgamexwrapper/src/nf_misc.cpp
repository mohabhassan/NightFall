#include "nf_misc.h"
#include <wolfssl/wolfcrypt/md5.h>
#include "dgamex86.h"

bool md5File(const char* file_name, char md5Str[MD5_STR_SIZE])//MD5_DIGEST_SIZE*2+1
{
	unsigned char md5sum[MD5_DIGEST_SIZE];
	FILE* fp;
	long filelen = 0, bytesread = 0;
	errno_t err;
	char* buff;
	Md5 md5;
	err = fopen_s(&fp, file_name, "rb");
	if (err != 0)
	{
		return false;
	}
	fseek(fp, 0, SEEK_END);
	filelen = ftell(fp);
	rewind(fp);

	try
	{
		buff = new char[filelen + 1];
	}
	catch (...)
	{
		return false;
	}
	buff[filelen] = '\0';

	bytesread = fread(buff, 1, filelen, fp);
	if (bytesread < filelen)
	{
		delete[] buff;
		fclose(fp);
		return false;
	}
	fclose(fp);


	wc_InitMd5(&md5);

	wc_Md5Update(&md5, (const unsigned char*)buff, filelen);

	wc_Md5Final(&md5, md5sum);

	md5Str = { 0 };
	for (int di = 0; di < MD5_DIGEST_SIZE; ++di)
		sprintf(md5Str + di * 2, "%02x", md5sum[di]);
	delete[] buff;
	return true;
}



bool validateIP(const char* ip) {
	int b1 = 0, b2 = 0, b3 = 0, b4 = 0;
	constexpr int buffLen = 64;
	char ipbuffer[buffLen] = { 0 };
	int i = 0;

	strcpy(ipbuffer, ip);

	for (i = 0; i < buffLen; i++) {
		if (ipbuffer[i] == '*') ipbuffer[i] = '0';
	}

	if (sscanf_s(ipbuffer, "%i.%i.%i.%i", &b1, &b2, &b3, &b4) != 4)
		return false;

	if (b1 < 0 || b2 < 0 || b3 < 0 || b4 < 0 || b1 > 255 || b2 > 255 || b3 > 255 || b4 > 255)
		return false;

	return true;
}


/* Allows sending messages to client */
/* Use message types defined in misc.h */
// This version works but causes warnings during compilation since original SendServerCommand function uses client_t pointer instead of clientNum
void SendGameMessage(int clientNum, char message_type, const char* text, ...)
{
	char buffer[4000];  // better not to go higher
	va_list argptr;
	va_start(argptr, text);
#ifdef MSVC6
	// possible overflow here
	vsprintf(buffer, text, argptr);
#else
	vsnprintf(buffer, 4000, text, argptr);
#endif
	buffer[3999] = '\0';
	va_end(argptr);

	gi->SendServerCommand(clientNum, "print \"%c%s\"", message_type, buffer);

}



char* Info_ValueForKey(const char* s, const char* key) {
	char	pkey[BIG_INFO_KEY];
	static	char value[2][BIG_INFO_VALUE];	// use two buffers so compares
											// work without stomping on each other
	static	int	valueindex = 0;
	char* o;

	if (!s || !key) {
		return "";
	}

	if (strlen(s) >= BIG_INFO_STRING) {
		gi->Error(ERR_DROP, "Info_ValueForKey: oversize infostring");
	}

	valueindex ^= 1;
	if (*s == '\\')
		s++;
	while (true)
	{
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value[valueindex];

		while (*s != '\\' && *s)
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;

		if (!stricmp(key, pkey))
			return value[valueindex];

		if (!*s)
			break;
		s++;
	}

	return "";
}


//CheckFPSSkin
//checks if userinfo skin has "_fps" inside
//returns true if player should be kicked.
bool CheckFPSSkin(char* userinfo)
{
	char skinallies[257];
	char skinaxis[257];
	//strncpy( skinallies, Info_ValueForKey(userinfo, "dm_playermodel"), sizeof(skinallies) );
	//strncpy( skinaxis, Info_ValueForKey(userinfo, "dm_playergermanmodel"), sizeof(skinallies) );
	strncpy(skinallies, Info_ValueForKey(userinfo, "dm_playermodel"), 256);
	strncpy(skinaxis, Info_ValueForKey(userinfo, "dm_playergermanmodel"), 256);
	skinallies[256] = '\0';
	skinaxis[256] = '\0';

	return (strstr(skinallies, "_fps") || strstr(skinaxis, "_fps"));
}

bool CheckCommentSlashesInName(char* name)
{
	int len = strlen(name);
	return name[len - 2] == '/' && (name[len - 1] == '/' || name[len - 1] == '*');
}