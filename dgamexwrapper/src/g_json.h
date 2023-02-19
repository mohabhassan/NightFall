#pragma once
#include "ScriptVariable.h"
#include "nlohmann/json.hpp"
using namespace std;
// for convenience
using json = nlohmann::json;

void GameVarToJson(ScriptVariable &var, json & j);
void JsonToGameVar(json & j, ScriptVariable & var);