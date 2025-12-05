#include "Input.hpp"
#include "GameData.hpp"
#include "raylib.h"
#include <string>
#include "Utils.hpp"
#include "Logger.hpp"

namespace Input
{
    void DoInput()
    {
        if (debug)
        {
            if (IsMouseButtonPressed(0))
            {
                if (placementbuffer.size() > 1)
                {
                    placementbuffer.clear();
                }
                placementbuffer.push_back(GetMousePosition());
            }
            if (placementbuffer.size() > 1 && IsKeyPressed(KEY_C))
            {
                Logger::Log("text copied to clipboard");

                std::string result =
                    std::to_string(placementbuffer.at(0).x) + "X\n" +
                    std::to_string(placementbuffer.at(0).y) + "Y\n" +
                    std::to_string(Utils::GetSizeFromPositions(placementbuffer).x) + "X\n" +
                    std::to_string(Utils::GetSizeFromPositions(placementbuffer).y) + "Y"; 

                SetClipboardText(result.c_str());          
            }
        }

        if (IsKeyPressed(KEY_F2))
        {
            Logger::Log("quick saved!");
            SAVESYSTEM::SaveGame();
        }
        else if (IsKeyPressed(KEY_F3))
        {
            Logger::Log("quick loaded!");
            SAVESYSTEM::LoadGame();
        }
        
        if (IsKeyPressed(KEY_F11))
        {
            Logger::Log("fullscreen was disabled as a quick fix.");
            g_PlayerData.fullscreen = !g_PlayerData.fullscreen;
        }
    }
}