// Misc and custom user-written functions
// Added by Razorapid

#include <wolfssl/wolfcrypt/md5.h>
#ifndef _WIN32
	#define _GNU_SOURCE
#endif

#ifdef __MINGW32__
#include "windows.h"
#endif

#include "misc.h"
#include "dgamex86.h"

#ifndef __cplusplus
#include <stdbool.h>
#endif

#pragma warning(disable : 4244 4013 4996 4700)

#if defined(MSVC6) || defined(__MINGW32__)
	/*struct timespec {
		time_t tv_sec;
		long tv_nsec;
	};*/
#endif

/* ==============================
             game-related functions
     ==============================
*/

/* Allows sending messages to client */
/* Use message types defined in misc.h */
// This version works but causes warnings during compilation since original SendServerCommand function uses client_t pointer instead of clientNum
void SendGameMessage(int clientNum, char message_type, const char *text, ... )
{
	char buffer[4000];  // better not to go higher
	va_list argptr;
	va_start (argptr, text);
#ifdef MSVC6
	// possible overflow here
	vsprintf (buffer, text, argptr);
#else
	vsnprintf (buffer, 4000, text, argptr);
#endif
	buffer[3999] = '\0';
	va_end (argptr);

	gi.SendServerCommand(clientNum, "print \"%c%s\"", message_type, buffer);

}


// Wombat in his wrapper was claiming that passing NULL instead of clientNum to SendServerCommand will broadcast the message to everyone
// but since it didn't worked in MOHAA 1.0 so I made a function for broadcasting
// never tested passing NULL in 1.11, but this function will work the same way as passing NULL (if it works)
void BroadcastGameMessage(int maxClients, char message_type, const char *text, ... )
{
	int clientNum = 0;
	char buffer[4000];  // better not go higher

	va_list argptr;
	va_start (argptr, text);
#ifdef MSVC6
	// possible overflow here
	vsprintf (buffer, text, argptr);
#else
	vsnprintf (buffer, 4000, text, argptr);
#endif
	buffer[3999] = '\0';
	va_end (argptr);

	for(clientNum = 0; clientNum < maxClients; clientNum++)
	{
		gi.SendServerCommand(clientNum, "print \"%c%s\"", message_type, buffer);
	}
}


char *Info_ValueForKey(const char *s, const char *key) {
	char	pkey[BIG_INFO_KEY];
	static	char value[2][BIG_INFO_VALUE];	// use two buffers so compares
											// work without stomping on each other
	static	int	valueindex = 0;
	char	*o;

	if (!s || !key) {
		return "";
	}

	if (strlen(s) >= BIG_INFO_STRING) {
		gi.Error(ERR_DROP, "Info_ValueForKey: oversize infostring");
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
//
//void Info_SetValueForKey( char *s, const char *key, const char *value ) //not working
//{
//	char	newi[1350];
//	const char* blacklist = "\\;\"";
//
///*	if ( strlen( s ) >= MAX_INFO_STRING ) {
//		Com_Error( ERR_DROP, "Info_SetValueForKey: oversize infostring" );
//	}*/
//
//	for(; *blacklist; ++blacklist)
//	{
//		if (strchr (key, *blacklist) || strchr (value, *blacklist))
//		{
//			gi.Printf ("Can't use keys or values with a '%c': %s = %s\n", *blacklist, key, value);
//			return;
//		}
//	}
//	
//	Info_RemoveKey (s, key);
//	if (!value || !strlen(value))
//		return;
//
//	sprintf_s (newi, sizeof(newi), "\\%s\\%s", key, value);
//
///*	if (strlen(newi) + strlen(s) >= MAX_INFO_STRING)
//	{
//		Com_Printf ("Info string length exceeded\n");
//		return;
//	}*/
//
//	strcat (newi, s);
//	strcpy (s, newi);
//}

//void Info_RemoveKey( char *s, const char *key ) //not working
//{
//	char	*start;
//	char	pkey[512];
//	char	value[512];
//	char	*o;
//
//	//if ( strlen( s ) >= MAX_INFO_STRING ) {
//	//	Com_Error( ERR_DROP, "Info_RemoveKey: oversize infostring" );
//	//}
//
//	if (strchr (key, '\\')) {
//		return;
//	}
//
//	while (1)
//	{
//		start = s;
//		if (*s == '\\')
//			s++;
//		o = pkey;
//		while (*s != '\\')
//		{
//			if (!*s)
//				return;
//			*o++ = *s++;
//		}
//		*o = 0;
//		s++;
//
//		o = value;
//		while (*s != '\\' && *s)
//		{
//			if (!*s)
//				return;
//			*o++ = *s++;
//		}
//		*o = 0;
//
//		if (!strcmp (key, pkey) )
//		{
//			strcpy (start, s);	// remove this part
//			return;
//		}
//
//		if (!*s)
//			return;
//	}
//
//}
/* add a line to the server log with level and timestamp  */
void add_log(const char *level, const char *fmt, ...){
	int loggable = 0;
	char timestr[30];
	va_list argptr;
	loggable = ( (LOG_LEVEL==LOG_DEBUG)
			|| ((LOG_LEVEL==LOG_INFO) && (level!=LOG_DEBUG))
			|| ((LOG_LEVEL==LOG_WARNING) && (level!=LOG_DEBUG) && (level!=LOG_INFO))
			|| ((LOG_LEVEL==LOG_ERROR) && (level==LOG_ERROR)) );
	if (loggable){
		char text[4096];
		va_start (argptr, fmt);
		vsprintf (text, fmt, argptr);
		va_end (argptr);
		if (strlen(text)>0){
			if (text[strlen(text)-1]=='\n'){
				text[strlen(text)-1] = '\0';
			}
		}
		getDateTimeInto(timestr);
		if (gi.Printf != NULL){
			gi.Printf("[%s] %s : %s\n", timestr, level, text);
		} else { // should never happen, but who knows...
			printf("[%s] %s : %s\n", timestr, level, text);
		}
	}
}


void *MyMallocImpl( int size, const char * function, const char * file, int line ){
	void * ret = malloc(size);
	if (MEM_DEBUG){
		fprintf(stderr,"Allocated %d bytes of memory at %p [%s %s:%d]\n",size,ret,function,file,line);
	}
	return ret;
}

void MyFreeImpl( void *ptr, const char * function, const char * file, int line ){
	if (MEM_DEBUG){
		fprintf(stderr,"Freed memory at %p [%s %s:%d]\n",ptr,function,file,line);
	}
	free(ptr);
}
/* Allocate memory - with optional debug  info */
#define MyMalloc(size)  MyMallocImpl(size, __FUNCTION__, __FILE__, __LINE__)

/* Free memory - with optional debug info */
#define MyFree(ptr)	MyFreeImpl(ptr, __FUNCTION__, __FILE__, __LINE__)



/* ==============================
                   string functions
     ==============================
*/

void CreateRandomText(int length, char *returned_text)
{
	//This is where we'll put the randomly generated character
	int textChar;
    //This is where we'll keep track of how many characters we've generated already
    long counter = 0;
    //This variable will hold a random value between 0 and 1, both included
    float tempRand;
    //Here we seed the random generator with the gi.miliseconds in seconds
    srand(time(NULL));

	if(length <= 0) return;

	while (counter < length) {
            //So here we generate a random value between 0 and 1
            tempRand = (float) rand() / RAND_MAX;
            //If tempRand if smaller than 0.7, we're gonna generate a alphabetical character
            if (tempRand < .7) {
                //This generates a value between 0 and 26
                textChar = ((float) rand()/RAND_MAX) * 26;
                //If tempRand was smaller than 0.35 (half of 0.7, so it's 50/50 here) we generate a lowercase character
                if (tempRand < .35) {
                    textChar += 'a';
                } else {    //Otherwise it's gonna be an uppercase one
                    textChar += 'A';
                }
            } else {        //If temprand was bigger than 0.7, we generate a numerical character
                textChar = ((float) rand()/RAND_MAX) * 9;
                textChar += '0';
            }
            //Now we print the generated character
            *(returned_text+counter) = textChar;
            //And increment the iterator
            counter++;
        }
}

char* mystrndup (const char *s, size_t len) {
	char *d;
    if (strlen(s) < len){
		len = strlen(s);
    }
    //char *d = (char *)(malloc (len + 1));
	d = (char *)(MyMalloc (len + 1));
    if (d == NULL){
		return NULL;
    }
    strncpy (d,s,len);
    return d;
}

/* Return substring  of a string in a newly allocated buffer.  Don't forget to free the buffer! */
char* substring(const char* str, size_t begin, size_t len){
    const char* str2;
    if (str == NULL || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)){
		return NULL;
    }
    str2 = str + begin;
    return mystrndup(str2, len);
}

/* trim left whitespaces */
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

/* trim right whitespaces */
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

/* trim left and right whitespaces */
char *trim(char *s)
{
    return rtrim(ltrim(s));
}


/* Allocates a sufficient buffer and prints into it. Buffer must be free-d! Returns pointer to the buffer, or NULL if unsuccessful */
char * make_message(const char *fmt, ...) {
	/* Guess we need no more than 100 bytes. */
	int n, size = 100;
	char *p, *np;
	va_list ap;

	//if ((p = malloc (size)) == NULL){
	if ((p = (char*)MyMalloc (size)) == NULL){
		return NULL;
	}

	while (1) {
		/* Try to print in the allocated space. */
		va_start(ap, fmt);
#ifdef MSVC6
		// possible overflow here
#else
		n = vsprintf (p, fmt, ap);
#endif
		//n = vsnprintf (p, size, fmt, ap);
		va_end(ap);
		/* If that worked, return the string. */
		if (n > -1 && n < size){
			return p;
		}
		/* Else try again with more space. */
		if (n > -1){    /* glibc 2.1 */
			size = n+1; /* precisely what is needed */
		} else {           /* glibc 2.0 */
			size *= 2;  /* twice the old size */
		}
		if ((np = reinterpret_cast<char*>(realloc (p, size))) == NULL) {
			//free(p);
			MyFree(p);
			return NULL;
		} else {
			p = np;
		}
	}
}


/* ==============================
           date and time functions
     ==============================
*/

/* Prints current date and time into the buffer in YYYY.MM.DD hh:mm:ss  format.   Buffer should have enough space for at least 20 chars. */
void getDateTimeInto(char *buf){
	size_t i;
	struct tm tim;
	time_t now;
	now = time(NULL);
	tim = *(localtime(&now));
	i = strftime(buf,20,"%Y.%m.%d %H:%M:%S",&tim);
}

/* sleep for the specified number of milliseconds */
int msleep(unsigned long milisec) {
#if defined(MSVC6) || defined(__MINGW32__)
	Sleep(milisec);
#else
	struct timespec req={0};
	time_t sec=(int)(milisec/1000);
	milisec=milisec-(sec*1000);
	req.tv_sec=sec;
	req.tv_nsec=milisec*1000000L;
	while(nanosleep(&req,&req)==-1)
		continue;
#endif

	return 1;
}

/* get the current time in relative milliseconds (useful for measuring elapsed time in the code) */
unsigned long clockMsec(){
	unsigned long ret;
	unsigned long CLOCKS_PER_MSEC = (CLOCKS_PER_SEC / 1000);
	clock_t cl;
	cl = clock();
	add_log(LOG_INFO, "clock1");
	add_log(LOG_INFO, "clock2");
	add_log(LOG_INFO, "clock3: %ld",CLOCKS_PER_MSEC);
	if (CLOCKS_PER_MSEC==0){
		return 0;
	}
	ret = cl / CLOCKS_PER_MSEC;
	add_log(LOG_INFO, "clock4: %ld",ret);
	return ret;
}

/* parses a string as an int, returns int value on success, the specified errorvalue on parse error (or partial match if it's not allowed)  */
int parseint(const char *str, int mustbefullmatch, int errorvalue){
	char *tail;
	int value;
	errno = 0;
	value = strtol(str, &tail, 10);
	if (errno != 0){
		return errorvalue;
	}
	if ((tail[0]!='\0') && mustbefullmatch){
		return errorvalue;
	}
	return value;
}



bool validateIP(const char *ip) {
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

bool md5File(const char* file_name, char md5Str[MD5_DIGEST_SIZE * 2 + 1])
{
	unsigned char md5sum[MD5_DIGEST_SIZE];
	FILE *fp;
	long filelen = 0, bytesread = 0;
	errno_t err;
	char *buff;
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


	for (int di = 0; di < MD5_DIGEST_SIZE; ++di)
		sprintf(md5Str + di * 2, "%02x", md5sum[di]);
	delete[] buff;
	return true;
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
// =================================================================
// Custom signal handling (linux only) to print info on application crashes
// =================================================================

#ifndef _WIN32

// original signal handlers
struct sigaction origSignalActions[NSIG];

void initsighandlers(){
	if (CUSTOM_SIGNAL_HANDLERS){
		/* Install our signal handlers */
		struct sigaction sa;

		sa.sa_sigaction = (void *)sighandler;
		sigemptyset (&sa.sa_mask);
		sa.sa_flags = SA_RESTART | SA_SIGINFO;

		sigaction(SIGSEGV, &sa, &origSignalActions[SIGSEGV]);
		sigaction(SIGFPE, &sa, &origSignalActions[SIGFPE]);
		sigaction(SIGILL, &sa, &origSignalActions[SIGILL]);
		sigaction(SIGBUS, &sa, &origSignalActions[SIGBUS]);
		sigaction(SIGABRT, &sa, &origSignalActions[SIGABRT]);
		sigaction(SIGSYS, &sa, &origSignalActions[SIGSYS]);
	}
}

void resetsighandlers(){
	if (CUSTOM_SIGNAL_HANDLERS){
		sigaction(SIGSEGV, &origSignalActions[SIGSEGV], NULL);
		sigaction(SIGFPE, &origSignalActions[SIGFPE], NULL);
		sigaction(SIGILL, &origSignalActions[SIGILL], NULL);
		sigaction(SIGBUS, &origSignalActions[SIGBUS], NULL);
		sigaction(SIGABRT, &origSignalActions[SIGABRT], NULL);
		sigaction(SIGSYS, &origSignalActions[SIGSYS], NULL);
	}
}

void sighandler(int sig, siginfo_t *info, void *secret) {

  void *trace[100];
  char **messages = (char **)NULL;
  int i, trace_size = 0;
  ucontext_t *uc = (ucontext_t *)secret;

  char * signame = strsignal(sig);

  /* Do something useful with siginfo_t */
  if (sig == SIGSEGV){
	if (gi.Printf != NULL){
		gi.Printf("Got signal %d - %s, faulty address is %p\n", sig, signame, info->si_addr);
	} else {
		printf("Got signal %d - %s, faulty address is %p\n", sig, signame, info->si_addr);
	}
  } else {
	if (gi.Printf != NULL){
		gi.Printf("Got signal %d - %s\n", sig, signame);
	} else {
		printf("Got signal %d - %s\n", sig, signame);
	}
  }

  trace_size = backtrace(trace, 100);
  /* overwrite sigaction with caller's address */
  trace[1] = (void *) uc->uc_mcontext.gregs[REG_EIP];

  messages = backtrace_symbols(trace, trace_size);

  if (gi.Printf != NULL){
	gi.Printf("Execution path:\n");
  } else {
	printf("Execution path:\n");
  }

  for (i=1; i<trace_size; ++i){ /* skip first stack frame (points here) */
    if (gi.Printf != NULL){
		gi.Printf(" --> %s\n", messages[i]);
	} else {
		printf(" --> %s\n", messages[i]);
	}
  }

  free(messages);

  resetsighandlers();  // reset original MOHAA or default signal handlers, so no more signals are handled by this handler (a signal is considered to be a fatal program error, the original implementations should exit)

  raise(sig);
}

#endif
