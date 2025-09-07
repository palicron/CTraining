#pragma once


struct EngineConfig
{
    int targetFPS;
    int width;
    int height;
    bool fullscreen;

    EngineConfig() : targetFPS(60), width(1200), height(850), fullscreen(false)
    {
    }

    EngineConfig(const int InTarget,const int InWidth, const int InHeight, const bool InFullScreen) : targetFPS(InTarget), width(InWidth), height(InHeight), fullscreen(InFullScreen)
    {
    }
};
