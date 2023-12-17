#pragma once
#include <string>
using std::string;
class UpdateClient
{
	string RequestUpdateInfo();
	bool UpdateFile(string fileRelPath, string fileURL, string fileMD5);
public:
	UpdateClient();
	~UpdateClient();
	void CheckForUpdate();
};

