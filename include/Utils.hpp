#pragma once

#include "raylib.h"
#include <string>
#include <vector>

namespace Utils
{
    enum ButtonReturns
    {
        None,
        Hovering,
        Clicked
    };

    extern Vector2 GetSizeFromPositions(const std::vector<Vector2> vec);

    extern float Clamp(float value,float min,float max);

    extern ButtonReturns InvisibleButton(Rectangle bounds,Vector2 mousepoint = {0,0});

    extern void RenderMousePos();
}