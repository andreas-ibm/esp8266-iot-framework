#include <EEPROM.h>

#include "configManager.h"

//class functions
bool config::begin(int numBytes)
{
    _hasConfigChanged = true;
    EEPROM.begin(numBytes);

    uint32_t storedVersion;
    EEPROM.get(0, storedVersion);
    if (storedVersion != configVersion)
    {        
        reset();
        return false;
    }
    else
    {
        EEPROM.get(4, data);

        return true;
    }
}

void config::reset()
{
    memcpy_P(&data, &defaults, sizeof(data));
    save();
}

void config::saveRaw(uint8_t newData[])
{
    memcpy(&data, newData, sizeof(data));
    save();
}

void config::saveExternal(configData *extData)
{
    memcpy(&data, extData, sizeof(data));
    save();
}

void config::save()
{
    EEPROM.put(0, configVersion);
    EEPROM.put(4, data);
    EEPROM.commit();
    _hasConfigChanged = true;
}

bool config::hasConfigChanged()
{
    bool hasChanged = _hasConfigChanged;
    _hasConfigChanged = false;
    return hasChanged;
}

config configManager;