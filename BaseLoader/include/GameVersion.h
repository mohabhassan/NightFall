#pragma once
#include <unordered_map>
#include <string>
using namespace std;
class GameInfo
{
public:
	enum Expansion { AA, SH, BT };
	enum Side { Client,	Server };
private:
	Expansion gameExpansion;
	Side gameSide;
	int gameVersion;
	string mainPath;
	string dgamex86Path;
	string system86Name;
public:
	GameInfo()
	{

	}
	void Init(Expansion game_expansion, Side game_side, int game_version)
	{
		gameExpansion = game_expansion;
		gameSide = game_side;
		gameVersion = game_version;

		mainPath = "default";
		dgamex86Path = "default";
		system86Name = "default";
		if (game_side == Client)
		{
			if (game_expansion == BT)
			{
				mainPath = "maintt";
				dgamex86Path = mainPath + "\\gamex86mohbt.dll";
				system86Name = "system86tt.dll";
			}
		}
		else if(game_side == Server)
		{
			if (game_expansion == AA)
			{
				mainPath = "main";
				dgamex86Path = mainPath + "\\gamex86mohaa.dll";
				system86Name = "system86.dll";
			}
			else if (game_expansion == SH)
			{
				mainPath = "mainta";
				dgamex86Path = mainPath + "\\dgamex86mohsh.dll";
				system86Name = "system86ta.dll";
			}
			else if (game_expansion == BT)
			{
				mainPath = "maintt";
				dgamex86Path = mainPath + "\\dgamex86mohbt.dll";
				system86Name = "system86tt.dll";
			}
		}

	}

	const Expansion GetExpansion()
	{
		return gameExpansion;
	}
	const Side GetSide()
	{
		return gameSide;
	}
	const int GetVersion()
	{
		return gameVersion;
	}
	const string GetMainPath()
	{
		return mainPath;
	}
	const string GetDgamex86Path()
	{
		return dgamex86Path;
	}
	const string GetSystem86Name()
	{
		return system86Name;
	}
};
//todo: init this variable.
extern GameInfo gameInfo;

#define MAIN_PATH gameInfo.GetMainPath()
#define DGAMEX86_PATH gameInfo.GetDgamex86Path()
#define SYSTEM86_NAME gameInfo.GetSystem86Name()