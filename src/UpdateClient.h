#pragma once
#include "misc.h"
#include <string>
using namespace std;
class UpdateClient
{
	string RequestUpdateInfo();
	bool UpdateFile(string fileRelPath, string fileURL, string fileMD5);
public:
	UpdateClient();
	~UpdateClient();
	void CheckForUpdate();
};

