#include "Logger.hpp"
#include <vector>
#include <string>
#include "raylib.h"
#include "Utils.hpp"

namespace Logger
{
    std::vector<std::string> logs;

    void RenderLogger()
    {
        for (int i = 0; i < logs.size(); i++)
        {
            DrawText(logs[i].c_str(),10,0 + 20 * Utils::Clamp(i + 1,1,INT_MAX),20,{255,255,255,(unsigned char)(255 - 40 * Utils::Clamp(i + 1,1,INT_MAX))});
        }
        return;
    }
    
    void Log(std::string message)
    {
        if (logs.size() + 1 > 5) {
            logs.pop_back();
            logs.push_back(message);
        }else {
            logs.push_back(message);
        }
        return;
    }
}