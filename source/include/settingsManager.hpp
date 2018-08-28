#pragma once
#include "types.hpp"
#include <sstream>
#include "yaml-cpp/yaml.h"
#include <fstream>

namespace qore
{
namespace game
{

//Class for handling default and user-defined settings
class SettingsManager
{

public:
    inline SettingsManager(){}

    void loadSettings(const string_t& fileName);
    void loadSettingsDefault(const string_t& fileName);

    // Generic method to set user setting
    template<typename T>
    void set(const string_t &category,const string_t& key,const T& value){
        userSettingsNode[category][key]=value;
    }

    // Generic method to get setting from settings.
    // If the user setting do not exist, the value from the default settings will be returned.
    template<typename T>
    T get(const string_t& category,const string_t& key)
    {

        if (userSettingsNode[category][key].IsDefined())
        {
            return userSettingsNode[category][key].as<T>();
        }
        else
        {
           return defaultSettingsNode[category][key].as<T>();
        }
    }

    // Aliases to settingsManager::get<T> for easier access
    string_t getString(const string_t& category,const string_t& key);

    int getInt(const string_t& category,const string_t& key);

    double getDouble(const string_t& category,const string_t& key);

    bool getBool(const string_t& category,const string_t& key);

    // Functions for saving files
    void save();
    void saveAs(const string_t& fileName);



    string_t getUserSettingsFileName() const;

    string_t getDefaultSettingsFileName() const;

protected:

    string_t userSettingsFileName;
    string_t defaultSettingsFileName;

    YAML::Node userSettingsNode;
    YAML::Node defaultSettingsNode;

};

} // namespace game

} // namespace qore
