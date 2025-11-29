#include "GameData.hpp"
#include <vector>
#include "STD.hpp"
#include "raylib.h"

PlayerData g_PlayerData;

bool shouldclose = false;

bool debug = false;

std::vector<Vector2> placementbuffer;

namespace SAVESYSTEM
{
    void SaveGame()
    {
        using namespace DG2D::SmartTableDatabase;

        SetValue("sawWarning", g_PlayerData.sawWarning ? "1" : "0");
        SetValue("health", std::to_string(g_PlayerData.health));
        SetValue("debt", std::to_string(g_PlayerData.debt));
        SetValue("cash", std::to_string(g_PlayerData.cash));

        SetValue("currentlocation", std::to_string((int)g_PlayerData.currentlocation));

        SetValue("inv_count", std::to_string(g_PlayerData.inventory.size()));

        for (size_t i = 0; i < g_PlayerData.inventory.size(); i++)
        {
            SetValue("inv_" + std::to_string(i),
                    std::to_string((int)g_PlayerData.inventory[i]));
        }

        SetValue("loc_count", std::to_string(g_PlayerData.locations.size()));

        for (size_t i = 0; i < g_PlayerData.locations.size(); i++)
        {
            const auto& L = g_PlayerData.locations[i];

            SetValue("loc_" + std::to_string(i) + "_v", L.visited ? "1" : "0");
            SetValue("loc_" + std::to_string(i) + "_l", L.locked ? "1" : "0");
            SetValue("loc_" + std::to_string(i) + "_t",
                    std::to_string((int)L.location));
        }
    }

    void LoadGame()
    {
        using namespace DG2D::SmartTableDatabase;

        g_PlayerData.sawWarning = (LoadValue("sawWarning") == "1");
        g_PlayerData.health = std::stoi(LoadValue("health"));
        g_PlayerData.debt = std::stoi(LoadValue("debt"));
        g_PlayerData.cash = std::stoi(LoadValue("cash"));

        g_PlayerData.currentlocation =
            (Locations)std::stoi(LoadValue("currentlocation", "0"));

        g_PlayerData.inventory.clear();
        int inv_count = std::stoi(LoadValue("inv_count", "0"));

        for (int i = 0; i < inv_count; i++)
        {
            std::string key = "inv_" + std::to_string(i);
            g_PlayerData.inventory.push_back(
                (Items)std::stoi(LoadValue(key, "0"))
            );
        }

        g_PlayerData.locations.clear();
        int loc_count = std::stoi(LoadValue("loc_count", "0"));

        for (int i = 0; i < loc_count; i++)
        {
            locationstate L;
            L.visited  = (LoadValue("loc_" + std::to_string(i) + "_v", "0") == "1");
            L.locked   = (LoadValue("loc_" + std::to_string(i) + "_l", "0") == "1");
            L.location = (Locations)std::stoi(
                LoadValue("loc_" + std::to_string(i) + "_t", "0")
            );

            g_PlayerData.locations.push_back(L);
        }
    }
}