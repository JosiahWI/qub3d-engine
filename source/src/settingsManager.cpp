#include "settingsManager.hpp"
#include "logging/logging.hpp"

using namespace qore::game;

void SettingsManager::loadSettings(const string_t &fileName)
{
    userSettingsFileName = fileName;
    INFO("Loading user settings from " + userSettingsFileName + "...");

    if (std::ifstream(fileName)){
        userSettingsNode = YAML::LoadFile(fileName);

        //Log all user-redefined settings
        for (YAML::const_iterator it = userSettingsNode.begin();it!=userSettingsNode.end();++it)
        {
            if(it->second.IsMap()){

                DEBUG(it->first.as<string_t>() + ":");
                for (YAML::const_iterator nestedIt = it->second.begin();
                     nestedIt!=it->second.end();
                     ++nestedIt)
                {
                    DEBUG(" "  + nestedIt->first.as<string_t>()
                                + ":" + nestedIt->second.as<string_t>() );
                }
            }
        }

        INFO("User settings loading completed");
    }
    else
    {
        WARNING("User settings file not found");
    }
}

void SettingsManager::loadSettingsDefault(const string_t &fileName)
{
    defaultSettingsFileName = fileName;

    INFO("Loading default settings from " + defaultSettingsFileName + "...");

    defaultSettingsNode = YAML::LoadFile(fileName);

    INFO("Default settings loading completed");
}

string_t SettingsManager::getString(const string_t &category, const string_t &key)
{
    return get<string_t>(category,key);
}

int SettingsManager::getInt(const string_t &category, const string_t &key)
{
    return get<int>(category,key);
}

double SettingsManager::getDouble(const string_t &category, const string_t &key)
{
    return get<double>(category,key);
}

bool SettingsManager::getBool(const string_t &category, const string_t &key)
{
    return get<bool>(category,key);
}

void SettingsManager::save()
{
    saveAs(userSettingsFileName);
}

void SettingsManager::saveAs(const string_t& fileName)
{
    INFO("Saving user settings to" + fileName + "...");

    std::ofstream stream;
    stream.open(fileName);

    YAML::Emitter em;
    em<<userSettingsNode;
    stream<<em.c_str();

    stream.close();
}

string_t SettingsManager::getUserSettingsFileName() const
{
    return userSettingsFileName;
}

string_t SettingsManager::getDefaultSettingsFileName() const
{
    return defaultSettingsFileName;
}
