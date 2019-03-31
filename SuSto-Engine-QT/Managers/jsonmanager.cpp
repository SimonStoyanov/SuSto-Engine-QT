#include "jsonmanager.h"
#include "globals.h"

JsonManager* JsonManager::instance = nullptr;

JsonManager::JsonManager()
{

}

JsonDoc* JsonManager::LoadJSON(const std::string& path)
{
    JsonDoc* ret = nullptr;

    const char* c_path = path.c_str();

	bool exists = false;
    for (std::list<JsonDoc*>::iterator it = jsons.begin(); it != jsons.end(); it++)
	{
        if (path.compare((*it)->GetPath()) == 0)
		{
			ret = (*it);
			exists = true;
			break;
		}
	}

	if (!exists)
	{
        JSON_Value *user_data = json_parse_file(c_path);
		JSON_Object *root_object = json_value_get_object(user_data);

		if (user_data == nullptr || root_object == nullptr)
		{
            //SPOOKYLOG("Error loading %s", c_path);
		}
		else
		{
            JsonDoc* new_doc = new JsonDoc(user_data, root_object, c_path);
			jsons.push_back(new_doc);

			ret = new_doc;
		}
	}

	return ret;
}


JsonDoc* JsonManager::CreateJSON(const std::string& path, const std::string& name, const std::string& extension)
{
    JsonDoc* ret = nullptr;

    std::string filepath = path + name + std::string(".") + extension;

    ret = CreateJSON(filepath);

	return ret;
}

JsonDoc * JsonManager::CreateJSON(const std::string& filepath)
{
    JsonDoc* ret = nullptr;

	bool exists = false;
    for (std::list<JsonDoc*>::iterator it = jsons.begin(); it != jsons.end(); it++)
	{
        if (filepath.compare((*it)->GetPath()) == 0)
		{
			exists = true;
			break;
		}
	}

	if (exists)
	{
        //INTERNAL_LOG("Error creating %s. There is already a file with this path/name", filepath);
	}
	else
	{
		JSON_Value* root_value = json_value_init_object();

		if (root_value == nullptr)
		{
            //INTERNAL_LOG("Error creating %s. Wrong path?", filepath);
		}
		else
		{
			JSON_Object* root_object = json_value_get_object(root_value);

            JsonDoc* new_doc = new JsonDoc(root_value, root_object, filepath.c_str());
			jsons.push_back(new_doc);

			new_doc->Save();

			ret = new_doc;
		}
	}

	return ret;
}

void JsonManager::UnloadJSON(JsonDoc * json)
{
    if (json != nullptr)
	{
        for (std::list<JsonDoc*>::iterator it = jsons.begin(); it != jsons.end();)
		{
            if ((*it) == json)
			{
				(*it)->CleanUp();
                delete(*it);

				it = jsons.erase(it);
				break;
			}
			else
				++it;

		}
    }
}

void JsonManager::Start()
{

}

void JsonManager::UnloadAllJSONs()
{
    for (std::list<JsonDoc*>::iterator it = jsons.begin(); it != jsons.end(); ++it)
	{
		(*it)->CleanUp();
        delete(*it);
	}

	jsons.clear();
}

void JsonManager::CleanUp()
{
	UnloadAllJSONs();
}

JsonDoc::JsonDoc()
{
}

JsonDoc::JsonDoc(JSON_Value * _value, JSON_Object * _object, const char* _path)
{
	value = _value;
	object = _object;
	root = _object;
	path = _path;
}

JsonDoc::JsonDoc(const JsonDoc & doc)
{
	value = doc.value;
	object = doc.object;
	path = doc.path;
	root = object;
}

JsonDoc::~JsonDoc()
{
}

void JsonDoc::SetString(const std::string& set, const char * str)
{
	json_object_dotset_string(object, set.c_str(), str);
}

void JsonDoc::SetBool(const std::string& set, bool bo)
{
	json_object_dotset_boolean(object, set.c_str(), bo);
}

void JsonDoc::SetNumber(const std::string& set, double nu)
{
	json_object_dotset_number(object, set.c_str(), nu);
}

void JsonDoc::SetNumber2(const std::string & set, float2 val)
{
	SetArray(set);
	AddNumberToArray(set, val.x);
	AddNumberToArray(set, val.y);
}

void JsonDoc::SetNumber3(const std::string& set, float3 val)
{
	SetArray(set);
	AddNumberToArray(set, val.x);
	AddNumberToArray(set, val.y);
	AddNumberToArray(set, val.z);
}

void JsonDoc::SetNumber4(const std::string& set, float4 val)
{
	SetArray(set);
	AddNumberToArray(set, val.x);
	AddNumberToArray(set, val.y);
	AddNumberToArray(set, val.w);
	AddNumberToArray(set, val.z);
}

void JsonDoc::SetArray(const std::string& set)
{
	JSON_Value* va = json_value_init_array();
	JSON_Array* arr = json_value_get_array(va);

	json_object_dotset_value(object, set.c_str(), va);
}

bool JsonDoc::ArrayExists(const std::string & arr)
{
	bool ret = false;

	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
		ret = true;

	return ret;
}

void JsonDoc::ClearArray(const std::string& arr)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_clear(array);
	}
}

void JsonDoc::RemoveArrayIndex(const std::string & arr, int index)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_remove(array, index);
	}
}

int JsonDoc::GetArrayCount(const std::string& set) const
{
	int ret = 0;

	JSON_Array* array = json_object_dotget_array(object, set.c_str());

	if (array != nullptr)
	{
		ret = json_array_get_count(array);
	}

	return ret;
}

const char * JsonDoc::GetStringFromArray(const std::string& arr, int index)
{
	const char* ret = nullptr;

	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		if (FindArrayValue(arr.c_str(), index, json_value_type::JSONString))
		{
			ret = json_array_get_string(array, index);
		}
	}

	return ret;
}

bool JsonDoc::GetBoolFromArray(const std::string& arr, int index)
{
	bool ret = false;

	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		if (FindArrayValue(arr.c_str(), index, json_value_type::JSONBoolean))
		{
			ret = json_array_get_boolean(array, index);
		}
	}

	return ret;
}

double JsonDoc::GetNumberFromArray(const std::string& arr, int index)
{
	double ret = 0;

	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		if (FindArrayValue(arr.c_str(), index, json_value_type::JSONNumber))
		{
			ret = json_array_get_number(array, index);
		}
	}

	return ret;
}

float2 JsonDoc::GetNumber2FromArray(const std::string & arr, int index)
{
	float2 ret = float2::zero;

    JsonDoc section_doc = this->GetNode();

	if (section_doc.MoveToSectionFromArray(arr, index))
	{
		ret = section_doc.GetNumber2("number2");
	}

	return ret;
}

void JsonDoc::AddStringToArray(const std::string& arr, const char * str)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_append_string(array, str);
	}
}

void JsonDoc::AddBoolToArray(const std::string& arr, bool bo)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_append_boolean(array, bo);
	}
}

void JsonDoc::AddNumberToArray(const std::string& arr, double set)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_append_number(array, set);
	}
}

void JsonDoc::AddNumber2ToArray(const std::string & arr, float2 set)
{
	AddSectionToArray(arr);

	int section = GetArrayCount(arr);
	
	if (section > 0)
	{
        JsonDoc section_doc = this->GetNode();

		if (section_doc.MoveToSectionFromArray(arr, section - 1))
		{
			section_doc.SetNumber2("number2", set);
		}
	}
}

void JsonDoc::AddSectionToArray(const std::string& arr)
{
	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		json_array_append_value(array, json_value_init_object());
	}
}

bool JsonDoc::MoveToSectionFromArray(const std::string& arr, int index)
{
	bool ret = false;

	JSON_Array* array = json_object_dotget_array(object, arr.c_str());

	if (array != nullptr)
	{
		JSON_Object* obj = json_array_get_object(array, index);

		object = obj;
		ret = true;
	}

	return ret;
}

const char * JsonDoc::GetString(const std::string& str, const char* defaul)
{
	const char* ret = defaul;

	if(FindValue(str.c_str(), json_value_type::JSONString))
		ret = json_object_dotget_string(object, str.c_str());

	return ret;
}

bool JsonDoc::GetBool(const std::string& str, bool defaul)
{
	bool ret = defaul;

	if (FindValue(str.c_str(), json_value_type::JSONBoolean))
		ret = json_object_dotget_boolean(object, str.c_str());

	return ret;
}

double JsonDoc::GetNumber(const std::string& str, double defaul)
{
	double ret = defaul;

	if (FindValue(str.c_str(), json_value_type::JSONNumber))
		ret = json_object_dotget_number(object, str.c_str());

	return ret;
}

float2 JsonDoc::GetNumber2(const std::string & fl, float2 defaul)
{
	float2 ret = float2::zero;

	ret = defaul;

	JSON_Array* array = json_object_dotget_array(object, fl.c_str());

	if (array != nullptr)
	{
		ret.x = GetNumberFromArray(fl, 0);
		ret.y = GetNumberFromArray(fl, 1);
	}

	return ret;
}

float3 JsonDoc::GetNumber3(const std::string& fl, float3 defaul)
{
	float3 ret = float3::zero;

	ret = defaul;

	JSON_Array* array = json_object_dotget_array(object, fl.c_str());

	if (array != nullptr)
	{
		ret.x = GetNumberFromArray(fl, 0);
		ret.y = GetNumberFromArray(fl, 1);
		ret.z = GetNumberFromArray(fl, 2);
	}

	return ret;
}

float4 JsonDoc::GetNumber4(const std::string& fl, float4 defaul)
{
	float4 ret = float4::zero;

	ret = defaul;

	JSON_Array* array = json_object_dotget_array(object, fl.c_str());

	if(array != nullptr)
	{
		ret.x = GetNumberFromArray(fl, 0);
		ret.y = GetNumberFromArray(fl, 1);
		ret.w = GetNumberFromArray(fl, 2);
		ret.z = GetNumberFromArray(fl, 3);
	}

	return ret;
}

bool JsonDoc::MoveToSection(const std::string& set)
{
	bool ret = false;

	JSON_Object* obj = json_object_get_object(object, set.c_str());

	if (obj != nullptr)
	{
		object = obj;
		ret = true;
	}

	return ret;
}

void JsonDoc::RemoveSection(const std::string& set)
{
	json_object_remove(object, set.c_str());
}

void JsonDoc::MoveToRoot()
{
	object = root;
}

void JsonDoc::AddSection(const std::string& set)
{
	json_object_set_value(object, set.c_str(), json_value_init_object());
}

JsonDoc JsonDoc::GetNode()
{
    return JsonDoc(*this);
}

void JsonDoc::Clear()
{
	json_value_free(value);
	value = json_value_init_object();
	object = json_value_get_object(value);
	root = object;
}

std::string JsonDoc::GetPath()
{
	return path;
}

void JsonDoc::Save()
{
	json_serialize_to_file_pretty(value, path.c_str());
}

void JsonDoc::CleanUp()
{
	json_value_free(value);
}

bool JsonDoc::FindValue(const char * str, json_value_type type)
{
	bool ret = false;

	JSON_Value* val = json_object_dotget_value(object, str);

	if (val != nullptr && json_value_get_type(val) == type)
		ret = true;

	return ret;
}

bool JsonDoc::FindArrayValue(const char * arr, int index, json_value_type type)
{
	bool ret = false;

	JSON_Array* array = json_object_dotget_array(object, arr);

	if (array != nullptr)
	{
		JSON_Value* val = json_array_get_value(array, index);

		if (val != nullptr && json_value_get_type(val) == type)
			ret = true;
	}
	
	return ret;
}

DataAbstraction::DataAbstraction()
{
}

void DataAbstraction::Clear()
{
	ints.clear();
	bools.clear();
	floats.clear();
	strings.clear();
	floats2.clear();
	floats3.clear();
	floats4.clear();
}

void DataAbstraction::AddInt(const std::string & name, int val)
{
	ints[name] = val;
}

void DataAbstraction::AddBool(const std::string & name, bool val)
{
	bools[name] = val;
}

void DataAbstraction::AddFloat(const std::string & name, float val)
{
	floats[name] = val;
}

void DataAbstraction::AddString(const std::string & name, const std::string& val)
{
	strings[name] = val;
}

void DataAbstraction::AddFloat2(const std::string & name, const float2& val)
{
	floats2[name] = val;
}

void DataAbstraction::AddFloat3(const std::string & name, const float3& val)
{
	floats3[name] = val;
}

void DataAbstraction::AddFloat4(const std::string & name, const float4& val)
{
	floats4[name] = val;
}

void DataAbstraction::AddFloat2Vector(const std::string & name, const std::vector<float2> val)
{
	floats2_vector[name] = val;
}

int DataAbstraction::GetInt(const std::string & name, int def)
{
	std::map<std::string, int>::iterator it = ints.find(name);

	if (it != ints.end())
		return it->second;

	return def;
}

bool DataAbstraction::GetBool(const std::string & name, bool def)
{
	std::map<std::string, bool>::iterator it = bools.find(name);

	if (it != bools.end())
		return it->second;

	return def;
}

float DataAbstraction::GetFloat(const std::string & name, float def)
{
	std::map<std::string, float>::iterator it = floats.find(name);

	if (it != floats.end())
		return it->second;

	return def;
}

std::string DataAbstraction::GetString(const std::string & name, std::string def)
{
	std::map<std::string, std::string>::iterator it = strings.find(name);

	if (it != strings.end())
		return it->second;

	return def;
}

float2 DataAbstraction::GetFloat2(const std::string & name, float2 def)
{
	std::map<std::string, float2>::iterator it = floats2.find(name);

	if (it != floats2.end())
		return it->second;

	return def;
}

float3 DataAbstraction::GetFloat3(const std::string & name, float3 def)
{
	std::map<std::string, float3>::iterator it = floats3.find(name);

	if (it != floats3.end())
		return it->second;

	return def;
}

float4 DataAbstraction::GetFloat4(const std::string & name, float4 def)
{
	std::map<std::string, float4>::iterator it = floats4.find(name);

	if (it != floats4.end())
		return it->second;

	return def;
}

std::vector<float2> DataAbstraction::GetFloat2Vector(const std::string & name)
{
	std::map<std::string, std::vector<float2>>::iterator it = floats2_vector.find(name);

	if (it != floats2_vector.end())
		return it->second;

	return std::vector<float2>();
}

void DataAbstraction::Serialize(JsonDoc & doc)
{
	int counter = 0;
	if (ints.size() > 0)
	{
		doc.SetNumber("ints_count", ints.size());

		for (std::map<std::string, int>::iterator it = ints.begin(); it != ints.end(); ++it)
		{
			std::string int_name = "int_name_" + std::to_string(counter);
			std::string int_value = "int_value_" + std::to_string(counter);

			doc.SetString(int_name, (*it).first.c_str());
			doc.SetNumber(int_value, (*it).second);

			++counter;
		}
	}

	counter = 0;
	if (bools.size() > 0)
	{
		doc.SetNumber("bools_count", bools.size());

		for (std::map<std::string, bool>::iterator it = bools.begin(); it != bools.end(); ++it)
		{
			std::string bool_name = "bool_name_" + std::to_string(counter);
			std::string bool_value = "bool_value_" + std::to_string(counter);

			doc.SetString(bool_name, (*it).first.c_str());
			doc.SetBool(bool_value, (*it).second);

			++counter;
		}
	}

	counter = 0;
	if (floats.size() > 0)
	{
		doc.SetNumber("floats_count", floats.size());

		for (std::map<std::string, float>::iterator it = floats.begin(); it != floats.end(); ++it)
		{
			std::string float_name = "float_name_" + std::to_string(counter);
			std::string float_number = "float_value_" + std::to_string(counter);

			doc.SetString(float_name, (*it).first.c_str());
			doc.SetNumber(float_number, (*it).second);
			++counter;
		}
	}

	counter = 0;
	if (strings.size() > 0)
	{
		doc.SetNumber("strings_count", strings.size());

		for (std::map<std::string, std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
		{
			std::string string_name = "string_name_" + std::to_string(counter);
			std::string string_value = "string_value_" + std::to_string(counter);

			doc.SetString(string_name, (*it).first.c_str());
			doc.SetString(string_value, (*it).second.c_str());

			++counter;
		}
	}

	counter = 0;
	if (floats2.size() > 0)
	{
		doc.SetNumber("floats2_count", floats2.size());

		for (std::map<std::string, float2>::iterator it = floats2.begin(); it != floats2.end(); ++it)
		{
			std::string float2_name = "float2_name_" + std::to_string(counter);
			std::string float2_value = "float2_value_" + std::to_string(counter);

			doc.SetString(float2_name, (*it).first.c_str());
			doc.SetNumber2(float2_value, (*it).second);

			++counter;
		}
	}

	counter = 0;
	if (floats3.size() > 0)
	{
		doc.SetNumber("floats3_count", floats3.size());

		for (std::map<std::string, float3>::iterator it = floats3.begin(); it != floats3.end(); ++it)
		{
			std::string float3_name = "float3_name_" + std::to_string(counter);
			std::string float3_value = "float3_value_" + std::to_string(counter);

			doc.SetString(float3_name, (*it).first.c_str());
			doc.SetNumber3(float3_value, (*it).second);

			++counter;
		}
	}

	counter = 0;
	if (floats4.size() > 0)
	{
		doc.SetNumber("floats4_count", floats4.size());

		for (std::map<std::string, float4>::iterator it = floats4.begin(); it != floats4.end(); ++it)
		{
			std::string float4_name = "float4_name_" + std::to_string(counter);
			std::string float4_value = "float4_value_" + std::to_string(counter);

			doc.SetString(float4_name, (*it).first.c_str());
			doc.SetNumber4(float4_value, (*it).second);

			++counter;
		}
	}

	counter = 0;
	if (floats2_vector.size() > 0)
	{
		doc.SetNumber("floats2_vector_count", floats2_vector.size());

		for (std::map<std::string, std::vector<float2>>::iterator it = floats2_vector.begin(); it != floats2_vector.end(); ++it)
		{
			std::string float2_vector_name = "floats2_vector_name_" + std::to_string(counter);
			std::string float2_vector_value = "floats2_vector_value_" + std::to_string(counter);

			doc.SetString(float2_vector_name, (*it).first.c_str());

			doc.SetArray(float2_vector_value);

			std::vector<float2> floats2 = (*it).second;

			for (std::vector<float2>::iterator fl = floats2.begin(); fl != floats2.end(); ++fl)
			{
				doc.AddNumber2ToArray(float2_vector_value, (*fl));
			}

			++counter;
		}
	}
}

void DataAbstraction::DeSerialize(JsonDoc & doc)
{
	int ints_count = doc.GetNumber("ints_count", 0);
	int bools_count = doc.GetNumber("bools_count", 0);
	int floats_count = doc.GetNumber("floats_count", 0);
	int strings_count = doc.GetNumber("strings_count", 0);
	int floats2_count = doc.GetNumber("floats2_count", 0);
	int floats3_count = doc.GetNumber("floats3_count", 0);
	int floats4_count = doc.GetNumber("floats4_count", 0);
	int floats2_vector_count = doc.GetNumber("floats2_vector_count", 0);

	for (int i = 0; i < ints_count; ++i)
	{
		std::string int_name = "int_name_" + std::to_string(i);
		std::string int_value = "int_value_" + std::to_string(i);

		std::string name = doc.GetString(int_name.c_str());
		int val = doc.GetNumber(int_value.c_str());

		AddInt(name, val);
	}

	for (int i = 0; i < bools_count; ++i)
	{
		std::string bool_name = "bool_name_" + std::to_string(i);
		std::string bool_value = "bool_value_" + std::to_string(i);

		std::string name = doc.GetString(bool_name.c_str());
		bool val = doc.GetBool(bool_value.c_str());

		AddBool(name, val);
	}

	for (int i = 0; i < floats_count; ++i)
	{
		std::string float_name = "float_name_" + std::to_string(i);
		std::string float_value = "float_value_" + std::to_string(i);

		std::string name = doc.GetString(float_name.c_str());
		float val = doc.GetNumber(float_value.c_str());

		AddFloat(name, val);
	}

	for (int i = 0; i < strings_count; ++i)
	{
		std::string string_name = "string_name_" + std::to_string(i);
		std::string string_value = "string_value_" + std::to_string(i);

		std::string name = doc.GetString(string_name.c_str());
		std::string val = doc.GetString(string_value.c_str());

		AddString(name, val);
	}

	for (int i = 0; i < floats2_count; ++i)
	{
		std::string float2_name = "float2_name_" + std::to_string(i);
		std::string float2_value = "float2_value_" + std::to_string(i);

		std::string name = doc.GetString(float2_name.c_str());
		float2 val = doc.GetNumber2(float2_value.c_str());

		AddFloat2(name, val);
	}

	for (int i = 0; i < floats3_count; ++i)
	{
		std::string float3_name = "float3_name_" + std::to_string(i);
		std::string float3_value = "float3_value_" + std::to_string(i);

		std::string name = doc.GetString(float3_name.c_str());
		float3 val = doc.GetNumber3(float3_value.c_str());

		AddFloat3(name, val);
	}

	for (int i = 0; i < floats4_count; ++i)
	{
		std::string float4_name = "float4_name_" + std::to_string(i);
		std::string float4_value = "float4_value_" + std::to_string(i);

		std::string name = doc.GetString(float4_name.c_str());
		float4 val = doc.GetNumber4(float4_value.c_str());

		AddFloat4(name, val);
	}

	for (int i = 0; i < floats2_vector_count; ++i)
	{
		std::string floats2_vector_name = "floats2_vector_name_" + std::to_string(i);
		std::string floats2_vector_value = "floats2_vector_value_" + std::to_string(i);

		int array_count = doc.GetArrayCount(floats2_vector_value);

		std::string name = doc.GetString(floats2_vector_name.c_str());

		std::vector<float2> values;

		for (int y = 0; y < array_count; ++y)
		{
			float2 val = doc.GetNumber2FromArray(floats2_vector_value, y);

			values.push_back(val);
		}

		AddFloat2Vector(name, values);
	}
}
