#include "Utils.hpp"
#include "raylib.h"
#include <string>
#include <vector>
#include "raymath.h"

namespace Utils
{
    float Clamp(float value,float min,float max)
    {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }

    Vector2 GetSizeFromPositions(const std::vector<Vector2> vec)
    {
        if (vec.size() < 2)
            return { 0, 0 };

        int minX = std::min(vec[0].x, vec[1].x);
        int maxX = std::max(vec[0].x, vec[1].x);
        int minY = std::min(vec[0].y, vec[1].y);
        int maxY = std::max(vec[0].y, vec[1].y);

        return { (float)maxX - minX, (float)maxY - minY };
    }

    ButtonReturns InvisibleButton(Rectangle bounds,Vector2 mousepoint)
    {
        if (Vector2Equals(mousepoint,{0,0}))
        {
            mousepoint = GetMousePosition();
        }

        if (CheckCollisionPointRec(mousepoint, bounds))
        {
            if (IsMouseButtonPressed(0))
            {
                return Clicked;
            }else {
                return Hovering;
            }
        }
        return None;
    }

    void RenderMousePos()
    {
        DrawTextPro(
            GetFontDefault(),
            (std::to_string(GetMousePosition().x) + " || " + std::to_string(GetMousePosition().y)).c_str(),
            {0,200},
            {0,0},
            0,
            24,
            0.5f,
            WHITE
        );
        return;
    }
}