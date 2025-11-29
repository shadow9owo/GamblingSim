#include "Input.hpp"
#include "GameData.hpp"
#include "raylib.h"
#include <string>
#include "Utils.hpp"

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
                std::string result =
                    std::to_string(placementbuffer.at(0).x) + "X\n" +
                    std::to_string(placementbuffer.at(0).y) + "Y\n" +
                    std::to_string(Utils::GetSizeFromPositions(placementbuffer).x) + "X\n" +
                    std::to_string(Utils::GetSizeFromPositions(placementbuffer).y) + "Y"; 

                SetClipboardText(result.c_str());          
            }
        }
    }
}