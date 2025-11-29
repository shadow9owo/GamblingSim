#pragma once

#include "raylib.h"

namespace Render
{
    namespace Textures
    {
        extern Texture T_mainmenu;
        extern Texture T_phone;
        extern Texture T_DG;
        extern Texture T_Title;

        extern Texture T_Map;
        extern Texture T_Map_Overlay;

        extern Texture T_Map;
        extern Texture T_Map_Overlay;

        extern Texture T_scientologyhq;
        extern Texture T_standing_female_1;
        extern Texture T_standing_male_1;
        extern Texture T_standing_male_2;
        extern Texture T_standing_male_3;

        extern Texture T_casino;
        extern Texture T_alley;
        extern Texture T_abandonedhouse;

        extern Texture T_Home;

        extern Texture T_Factory;

        extern void Load();
        extern void Unload();
    }

    namespace Sounds
    {
        extern Sound Ring;

        extern void Load();
        extern void Unload();
    }

    namespace Fonts
    {
        extern void Load();
        extern void Unload();
    }

    namespace Music
    {
        extern void Load();
        extern void Unload();
    }

    extern void PrepUI();
    extern void RenderUI();
    extern void RenderCurrentLocation();
    extern void RenderCurrentLocationUI();
    extern void RenderCurrentScene();
}