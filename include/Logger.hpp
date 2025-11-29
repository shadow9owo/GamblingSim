#pragma once

#include <vector>
#include <string>

namespace Logger
{
    extern std::vector<std::string> logs;
    extern void RenderLogger();
    extern void Log(std::string message);
}