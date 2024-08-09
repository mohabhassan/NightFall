#pragma once
#include <string>
using std::string;
class UpdateClient
{
	bool updateOptionals = true;
	string RequestUpdateInfo();
	bool UpdateFile(string fileRelPath, string fileURL, string fileMD5, bool fileOptional);
public:
	UpdateClient();
	~UpdateClient();
	void CheckForUpdate();
};

