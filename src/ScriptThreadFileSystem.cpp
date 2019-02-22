#include "ScriptThread.h"
#include <algorithm>
#include <filesystem>

#define MAX_SCRIPTFILES 32

namespace fs = std::filesystem;

vector<FILE*> ScriptThread::scriptFiles;

void ScriptThread::FileSystemInit()
{

	cerSet.AddEventResponse(new Event(
		"fopen",
		EV_DEFAULT,
		"ss",
		"file_name access_type",
		"Opens file and returns file handle.",
		EV_RETURN
	),
		&ScriptThread::FOpenEvent);

	cerSet.AddEventResponse(new Event(
		"fclose",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Closes a file handle.",
		EV_RETURN
	),
		&ScriptThread::FCloseEvent);

	cerSet.AddEventResponse(new Event(
		"feof",
		EV_DEFAULT,
		"i",
		"file_handle",
		"End of file check",
		EV_RETURN
	),
		&ScriptThread::FEOFEvent);

	cerSet.AddEventResponse(new Event(
		"fseek",
		EV_DEFAULT,
		"iii",
		"file_handle offset origin",
		"Sets current file at given position",
		EV_RETURN
	),
		&ScriptThread::FSeekEvent);

	cerSet.AddEventResponse(new Event(
		"ftell",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Returns current file position w.r.t beginning of file.",
		EV_RETURN
	),
		&ScriptThread::FTellEvent);

	cerSet.AddEventResponse(new Event(
		"frewind",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Resets file's current postition.",
		EV_RETURN
	),
		&ScriptThread::FRewindEvent);

	cerSet.AddEventResponse(new Event(
		"fputc",
		EV_DEFAULT,
		"ii",
		"file_handle char",
		"Writes character to file at cursor position.",
		EV_RETURN
	),
		&ScriptThread::FPutcEvent);

	cerSet.AddEventResponse(new Event(
		"fputs",
		EV_DEFAULT,
		"is",
		"file_handle string",
		"Writes string to file at cursor position.",
		EV_RETURN
	),
		&ScriptThread::FPutsEvent);

	cerSet.AddEventResponse(new Event(
		"fgetc",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Reads character from file at cursor position.",
		EV_RETURN
	),
		&ScriptThread::FGetcEvent);

	cerSet.AddEventResponse(new Event(
		"fgets",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Reads string(full line) from file at cursor position.",
		EV_RETURN
	),
		&ScriptThread::FGetsEvent);

	cerSet.AddEventResponse(new Event(
		"ferror",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Returns error indicator for file.",
		EV_RETURN
	),
		&ScriptThread::FErrorEvent);

	cerSet.AddEventResponse(new Event(
		"fflush",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Flushes given file. Writes all unsaved data from stream buffer to stream.",
		EV_RETURN
	),
		&ScriptThread::FFlushEvent);

	cerSet.AddEventResponse(new Event(
		"fexists",
		EV_DEFAULT,
		"s",
		"filename",
		"Checks if file exists",
		EV_RETURN
	),
		&ScriptThread::FExistsEvent);

	cerSet.AddEventResponse(new Event(
		"freadall",
		EV_DEFAULT,
		"i",
		"file_handle",
		"Reads full file as string",
		EV_RETURN
	),
		&ScriptThread::FReadAllEvent);

	cerSet.AddEventResponse(new Event(
		"fsaveall",
		EV_DEFAULT,
		"is",
		"file_handle string",
		"Saves string to file.",
		EV_RETURN
	),
		&ScriptThread::FSaveAllEvent);

	cerSet.AddEventResponse(new Event(
		"fremove",
		EV_DEFAULT,
		"s",
		"filename",
		"Removes the file with given filename.",
		EV_RETURN
	),
		&ScriptThread::FRemoveEvent);

	cerSet.AddEventResponse(new Event(
		"frename",
		EV_DEFAULT,
		"ss",
		"oldname newname",
		"Renames the file with given oldname from oldname to newname.",
		EV_RETURN
	),
		&ScriptThread::FRenameEvent);

	cerSet.AddEventResponse(new Event(
		"fcopy",
		EV_DEFAULT,
		"ss",
		"from to",
		"Copies file.",
		EV_RETURN
	),
		&ScriptThread::FCopyEvent);

	cerSet.AddEventResponse(new Event(
		"freadpak",
		EV_DEFAULT,
		"s",
		"filename",
		"Reads file located inside .pk3 file in text mode and returns it's content as string.",
		EV_RETURN
	),
		&ScriptThread::FReadPakEvent);

	cerSet.AddEventResponse(new Event(
		"flist",
		EV_DEFAULT,
		"ssi",
		"path filter scanSubDirs",
		"List files inside path that match filter.",
		EV_RETURN
	),
		&ScriptThread::FListEvent);
}

void ScriptThread::FOpenEvent(Event *ev)
{
	FILE *fp = NULL;
	str filename, a_type;
	int argnum = ev->NumArgs();

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fopen!\n");
		return;
	}

	if (scriptFiles.size() == MAX_SCRIPTFILES)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fopen: Maximum number of concurrently open files exceed!\n");
		return;
	}


	filename = ev->GetString(1);
	a_type = ev->GetString(2);
	int err = fopen_s(&fp, filename.c_str(), a_type.c_str());

	if (err != 0)
	{
		fp = NULL;
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fopen: could not open file: %s with access: %s ! error code: %d\n", filename.c_str(), a_type.c_str(), err);
	}
	else
	{
		scriptFiles.push_back(fp);
	}

	ev->AddInteger((int)fp);
}


void ScriptThread::FCloseEvent(Event *ev)
{
	using namespace std;
	FILE *fp = NULL;
	int ret = 1;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fclose!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fclose: invalid file handle!\n");
	}
	else
	{
		ret = fclose(fp);
		scriptFiles.erase(it);
	}

	ev->AddInteger(ret);
}


void ScriptThread::FEOFEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = 0;
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for feof!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: feof: invalid file handle!\n");
	}
	else
	{
		ret = feof(fp);
	}
	ev->AddInteger(ret);
}




void ScriptThread::FSeekEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = 1;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 3)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fseek!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fseek: invalid file handle!\n");
	}
	else
	{
		int offset, origin;
		offset = ev->GetInteger(2);
		origin = ev->GetInteger(3);

		ret = fseek(fp, offset, origin);
	}

	ev->AddInteger(ret);
}


void ScriptThread::FTellEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = -1;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for ftell!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: ftell: invalid file handle!\n");
	}
	else
	{
		ret = ftell(fp);
	}
	ev->AddInteger(ret);
}


void ScriptThread::FRewindEvent(Event *ev)
{
	FILE *fp = NULL;
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for frewind!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: frewind: invalid file handle!\n");
	}
	else
	{
		rewind(fp);
	}
}



void ScriptThread::FPutcEvent(Event *ev)
{
	FILE *fp = NULL;
	str cStr = "";
	int ret = EOF;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fputc!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fputc: invalid file handle!\n");
	}
	else
	{
		cStr = ev->GetString(2);
		ret = fputc(cStr[0], fp);
	}

	ev->AddInteger(ret);
}


void ScriptThread::FPutsEvent(Event *ev)
{
	FILE *fp = NULL;
	str cStr = "";
	int ret = EOF;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fputs!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fputs: invalid file handle!\n");
	}
	else
	{
		cStr = ev->GetString(2);
		ret = fputs(cStr, fp);
	}

	ev->AddInteger(ret);
}


void ScriptThread::FGetcEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = EOF;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fgetc!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fgetc: invalid file handle!\n");
	}
	else
	{
		ret = fgetc(fp);
	}

	ev->AddInteger(ret);
}



void ScriptThread::FGetsEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = NULL;//error on default
	char *Str, *p;
	str retStr = "";
	int slen;
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fgets!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fgets: invalid file handle!\n");
	}
	else
	{
		slen = ev->GetInteger(2);
		if (slen <=0)
		{
			gi.Printf(PATCH_NAME " SCRIPT ERROR: fgets: invalid buffer size: %d!\n", slen);
		}
		else
		{
			slen++;
			try
			{
				Str = new char[slen];
			}
			catch (const std::bad_alloc& e)
			{
				gi.Printf(PATCH_NAME " SCRIPT ERROR: fgets: memory allocation error: %s !\n", e.what());
				ev->AddInteger(-1);
				delete Str;
				return;
			}
			p = fgets(Str, slen, fp);
			if (p == Str)
			{
				retStr = Str;
				ev->AddString(retStr);
			}
			else
			{
				ev->AddInteger((int)p);
			}
			delete Str;
		}

	}
}

void ScriptThread::FErrorEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = EOF;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for ferror!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: ferror: invalid file handle!\n");
	}
	else
	{
		ret = ferror(fp);
	}

	ev->AddInteger(ret);
}

void ScriptThread::FFlushEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = EOF;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fflush!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fflush: invalid file handle!\n");
	}
	else
	{
		ret = fflush(fp);
	}

	ev->AddInteger(ret);
}


void ScriptThread::FExistsEvent(Event *ev)
{
	str filename;
	int ret = 0;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fexists!\n");
		return;
	}

	filename = ev->GetString(1);
	if (filename == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL filename passed to fexists!\n");
		return;
	}

	try
	{
		fs::path filepath = fs::current_path() / filename.c_str();
		if (fs::exists(filepath))
		{
			ret = 1;
		}
	}
	catch (...)
	{
		//ret is already 0
	}

	ev->AddInteger(ret);
}

void ScriptThread::FReadAllEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = NULL;//error on default
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for freadall!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: freadall: invalid file handle!\n");
	}
	else
	{
		long size = 0;
		long currentPos = 0;//used for compatiblity
		long count;
		char *Str;
		currentPos = ftell(fp);

		fseek(fp, 0, SEEK_END);

		size = ftell(fp);

		fseek(fp, currentPos, SEEK_SET);

		Str = new (std::nothrow) char[size+1];
		if (!Str)
		{
			gi.Printf(PATCH_NAME " SCRIPT ERROR: freadall: memory allocation error!\n");
			delete Str;
			return;
		}

		count = fread(Str, sizeof(char), size, fp);
		Str[count] = NULL;
		ev->AddString(Str);
		delete Str;
	}
}


void ScriptThread::FSaveAllEvent(Event *ev)
{
	FILE *fp = NULL;
	int ret = EOF;//error on default
	str content;
	int argnum = ev->NumArgs();

	vector<FILE*>::iterator it;

	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fsaveall!\n");
		return;
	}

	fp = (FILE *)ev->GetInteger(1);

	it = find(scriptFiles.begin(), scriptFiles.end(), fp);
	if (it == scriptFiles.end())
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: fsaveall: invalid file handle!\n");
	}
	else
	{
		content = ev->GetString(2);

		if (content == NULL)
		{
			ret = -1;
			gi.Printf(PATCH_NAME " SCRIPT ERROR: fsaveall: content is NULL!\n");
		}
		else
		{
			ret = fwrite(content.c_str(), 1, content.length(), fp);
			errno_t err = errno;
		}

	}

	ev->AddInteger(ret);
}


void ScriptThread::FRemoveEvent(Event *ev)
{
	str filename;
	int ret = 0;//error on default
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fremove!\n");
		return;
	}

	filename = ev->GetString(1);
	
	if (filename == NULL )
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL filename passed to fremove!\n");
		return;
	}
	ret = remove(filename.c_str());

	ev->AddInteger(ret);
}


void ScriptThread::FRenameEvent(Event *ev)
{
	str oldname, newname;
	int ret = 0;//error on default
	int argnum = ev->NumArgs();


	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for frename!\n");
		return;
	}

	oldname = ev->GetString(1);
	newname = ev->GetString(2);

	if (oldname == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL oldname passed to frename!\n");
	}
	else if(newname == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL newname passed to frename!\n");
	}
	else
	{
		ret = rename(oldname.c_str(), newname.c_str());

		ev->AddInteger(ret);
	}
}



void ScriptThread::FCopyEvent(Event *ev)
{
	str from, to;
	int ret = -1;//error on default
	int argnum = ev->NumArgs();


	if (argnum != 2)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for fcopy!\n");
		return;
	}

	from = ev->GetString(1);
	to = ev->GetString(2);

	if (from == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL oldname passed to fcopy!\n");
	}
	else if (to == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL newname passed to fcopy!\n");
	}
	else
	{
		try
		{
			ret = fs::copy_file(from.c_str(), to.c_str()) ? 0 : -1;
		}
		catch (const std::exception& e)
		{
			gi.Printf(PATCH_NAME " SCRIPT ERROR: fcopy error: %s !\n", e.what());
		}

		ev->AddInteger(ret);
	}
}


void ScriptThread::FReadPakEvent(Event *ev)
{
	str filename;
	char *buf;
	int ret;//error on default
	int argnum = ev->NumArgs();


	if (argnum != 1)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for freadpak!\n");
		return;
	}

	filename = ev->GetString(1);

	if (filename == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL filename passed to freadpak!\n");
		return;
	}

	ret = gi.FS_ReadFile(filename, (void**)&buf);
	if (ret != -1)
	{
		ev->AddString(buf);
	}
	else
	{
		ev->AddInteger(ret);
	}
}


void ScriptThread::FListEvent(Event *ev)
{
	str path;
	str filter;
	int scanSubDirs = 0;
	int numFiles = 0;
	char *buf;
	int ret;//error on default
	char **list = NULL;
	int argnum = ev->NumArgs();
	ScriptVariable array;

	if (argnum != 3)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: Wrong number of arguments for flist!\n");
		return;
	}

	path = ev->GetString(1);

	if (path == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL path passed to flist!\n");
		return;
	}

	filter = ev->GetString(2);

	if (filter == NULL)
	{
		gi.Printf(PATCH_NAME " SCRIPT ERROR: NULL filter passed to flist!\n");
		return;
	}

	scanSubDirs = ev->GetInteger(3);

	list = gi.FS_ListFiles(path, filter, scanSubDirs, &numFiles);

	if (numFiles == 0)
	{
		gi.FS_FreeFileList(list);
		return;
	}
	for (int i = 0; i < numFiles; i++)
	{
		ScriptVariable index, value;
		sizeof(ScriptVariable);
		index.setIntValue(i);
		value.setStringValue(list[i]);
		sizeof(block_s<Entry<ScriptVariable,ScriptVariable>, MEM_BLOCKSIZE>);
		array.setArrayAtRef(index, value);
	}

	gi.FS_FreeFileList(list);

	ev->AddValue(array);
}