#pragma once

#include <vector>
#include "raylib.h"

namespace Minigames
{
    namespace Data
    {
        extern std::vector<Vector2> balllist;
    }

    enum Minigames_e
    {
        _None,
        _Slots,
        _Baggies_weed,
        _Baggies_heroine,
        _Shoot_cops,
        _Whip_followers,
        _Work
    };

    extern Minigames_e CurrentMinigame;

    extern void Work();
    extern void SlotsUI();
    extern void Baggies_weed(); // bag weed
    extern void Baggies_heroine(); // bag heroine
    extern void Shoot_Cops(); // Kult path

    extern void RenderCurrentMinUI();
}