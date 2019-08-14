#include "g_json.h"

void GameVarToJson(ScriptVariable & var, json & j)
{
	switch (var.GetType())
	{
	case VARIABLE_STRING:
	case VARIABLE_CONSTSTRING:
		j["type"] = "string";
		j["content"] = var.stringValue().c_str();
		break;
	case VARIABLE_INTEGER:
		j["type"] = "integer";
		j["content"] = var.intValue();
		break;
	case VARIABLE_FLOAT:
		j["type"] = "float";
		j["content"] = var.floatValue();
		break;
	case VARIABLE_CHAR:
		j["type"] = "char";
		j["content"] = var.charValue();
		break;
	case VARIABLE_ARRAY:
	{
		json arr_obj = json::object();
		Entry_scriptarrayholder		** const table = var.arrayValue()->arrayValue.getConSet().getTable();
		Entry_scriptarrayholder *entry;
		for (size_t i = 0; i < var.arrayValue()->arrayValue.getConSet().getTableLength(); i++)
		{
			for (entry = table[i]; entry != NULL; entry = entry->next)
			{
				ScriptVariable &key = entry->key;
				variabletype type = key.GetType();
				GameVarToJson(entry->value, arr_obj[key.stringValue().c_str()]);
			}
		}
		j["type"] = "array_object";
		j["content"] = arr_obj;
		break;
	}
	case VARIABLE_CONSTARRAY:
	{
		j["type"] = "array";
		ScriptConstArrayHolder * constArr = var.m_data.constArrayValue;
		for (size_t i = 0; i < constArr->size; i++)
		{
			ScriptVariable &e = constArr->constArrayValue[i + 1];
			GameVarToJson(e, j["content"][i]);
		}
		break;
	}
	case VARIABLE_VECTOR:
		j["type"] = "vector";
		j["content"]["x"] = var.vectorValue().x;
		j["content"]["y"] = var.vectorValue().y;
		j["content"]["z"] = var.vectorValue().z;
		break;
	case VARIABLE_CONTAINER:
	case VARIABLE_SAFECONTAINER:
	case VARIABLE_POINTER:
	case VARIABLE_LISTENER:
	case VARIABLE_REF:
	case VARIABLE_NONE:
		j["type"] = var.GetTypeName();
		j["content"] = nullptr;
		break;
	default:
		break;
	}
}

void JsonToGameVar(json & j, ScriptVariable & var)
{
	switch (j.type())
	{
	case json::value_t::null:
		var.setListenerValue(NULL);
		break;
	case json::value_t::string:
		var.setStringValue(string(j).c_str());
		break;
	case json::value_t::boolean:
		var.setIntValue(((bool)j) ? 1 : 0 );
		break;
	case json::value_t::number_integer:
	case json::value_t::number_unsigned:
		var.setIntValue((int)j);
		break;
	case json::value_t::number_float:
		var.setFloatValue((float)j);
		break;
	case json::value_t::array:
	{
		ScriptVariable elem;
		ScriptVariable index;
		for (size_t i = 0; i < j.size(); i++)
		{
			JsonToGameVar(j[i], elem);
			index.setIntValue(i);
			var.setArrayAtRef(index, elem);
		}
	}
		break;
	case json::value_t::object:
	{
		ScriptVariable index, value;
		for (json::iterator it = j.begin(); it != j.end(); ++it)
		{
			index.setStringValue(it.key().c_str());
			JsonToGameVar(it.value(), value);
			var.setArrayAtRef(index, value);
		}
	}
		break;
	default:
		break;
	}
}