#include "hashmap.h"

extern std::unordered_map<std::string, std::string> data_store;

void setKeyValue(const std::string &key, const std::string &value)
{
    data_store[key] = value;
}

std::string getValueForKey(const std::string &key)
{
    auto it = data_store.find(key);
    if (it != data_store.end())
    {
        return it->second;
    }
    else
    {
        return "KEY NOT FOUND";
    }
}
