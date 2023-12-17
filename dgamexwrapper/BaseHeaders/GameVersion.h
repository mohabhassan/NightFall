#pragma once
#include <string>
#include <unordered_map>
#include <tuple>

using std::string, std::unordered_map, std::tuple;
class GameInfo
{
public:
	enum Expansion { AA, SH, BT };
	enum Side { Client,	Server };
private:
	Expansion gameExpansion;
	Side gameSide;
	double gameVersion;
	string mainPath;
	string dgamex86Path;
	string system86Name;

	inline static unordered_map<string, tuple<Expansion, Side, double>> md5_game_info = { 
		{"5e6dbee412397e0a57be8c9b4592ba55", {AA, Server, 1.11}},
		{"418deeab51331c7a9e1051b60cba23d5", {BT, Server, 2.30}},
		{"ac58a6562cc8f53d2f3452b29902b54d", {BT, Server, 2.40}},
		{"1db701ce0f5cf29b8fa479f0898f7d08", {BT, Server, 2.40}},
		{"1162c8c26b7e0d687cbdaa2e52e5ae78", {SH, Server, 2.15}}
	};
	void InitMini(Expansion game_expansion, Side game_side, double game_version)
	{
		gameExpansion = game_expansion;
		gameSide = game_side;
		gameVersion = game_version;
	}

	void Init(Expansion game_expansion, Side game_side, double game_version)
	{
		InitMini(game_expansion, game_side, game_version);
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
		else if (game_side == Server)
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
public:
	GameInfo()
	{

	}

	bool InitFromMD5(string& md5)
	{
		using std::get;
		auto it = md5_game_info.find(md5);
		if (it == md5_game_info.end())
			return false;
		auto &tpl = it->second;
		Init(get<Expansion>(tpl), get<Side>(tpl), get<double>(tpl));
		return true;
	}

	const Expansion GetExpansion()
	{
		return gameExpansion;
	}
	const Side GetSide()
	{
		return gameSide;
	}
	const double GetVersion()
	{
		return gameVersion;
	}
	const bool IsClient()
	{
		return gameSide == Client;
	}
	const bool IsServer()
	{
		return gameSide == Server;
	}
	const bool IsAA()
	{
		return gameExpansion == AA;
	}
	const bool IsSH()
	{
		return gameExpansion == SH;
	}
	const bool IsBT()
	{
		return gameExpansion == BT;
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

extern GameInfo gameInfo;

#define MAIN_PATH gameInfo.GetMainPath()
#define DGAMEX86_PATH gameInfo.GetDgamex86Path()
#define SYSTEM86_NAME gameInfo.GetSystem86Name()