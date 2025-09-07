#include "../../Public/Utility/FileReader.h"

#include <stdexcept>

std::unique_ptr<EngineConfig> FileReader::LoadEngineConfig(const std::string& path)
{
    FILE* file = nullptr;
    
    errno_t err = fopen_s(&file, path.c_str(), "r");

    if (err != 0 || !file)
    {
        throw std::runtime_error("Failed to open file");
    }

    char buffer[1024];
    rapidjson::FileReadStream is(file, buffer, sizeof(buffer));
    rapidjson::Document document;
    document.ParseStream(is);
    fclose(file);

    if (!document.HasMember("InitialConfiguration") || !document["InitialConfiguration"].IsObject())
    {
        throw std::runtime_error("InitialConfiguration is Not part of the file");
    }

    const auto& initialConfig = document["InitialConfiguration"];
    const auto& WindowConfig = initialConfig["Window"];
    std::unique_ptr<EngineConfig> Config = std::make_unique<EngineConfig>(WindowConfig["TargetFPS"].GetInt(),
                                                                          WindowConfig["Width"].GetInt(), WindowConfig["Height"].GetInt(), WindowConfig["Fullscreen"].GetBool());

    return Config;
}
