#pragma once

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include "EngineTypes.h"

class FileReader
{
    
public:

    std::unique_ptr<EngineConfig> LoadEngineConfig(const std::string& path);
};
