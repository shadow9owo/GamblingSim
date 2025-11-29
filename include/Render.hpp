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

        extern Texture T_Slots1;
        extern Texture T_Slots2;

        extern Texture T_Factory;

        extern Texture T_Factory_Background;

        extern Texture T_Box;

        extern Texture T_scientologist;

        extern Texture T_basement;

        extern Texture T_knife;

        extern Texture T_table;

        extern Texture T_baggie;

        extern Texture T_heroine;

        extern Texture T_cop1;
        extern Texture T_cop2;
        extern Texture T_cop3;
        extern Texture T_cop4;

        extern Texture T_gunviewmodel;

        extern void Load();
        extern void Unload();
    }

    namespace Sounds
    {
        extern Sound select;
        extern Sound Ring;
        extern Sound WifeDialogue;
        extern Sound Gunshot;
        extern Sound Gambaspin;
        extern Sound plastic;
        extern Sound female_pain;
        extern Sound male_pain;
        extern Sound stab;

        extern void Load();
        extern void Unload();
    }

    namespace Fonts
    {
        extern void Load();
        extern void Unload();
    }

    namespace _Music
    {
        extern Music menutheme;
        extern Music gameambience;

        extern void Load();
        extern void Unload();
    }

    extern void PrepUI();
    extern void RenderUI();
    extern void RenderCurrentLocation();
    extern void RenderCurrentLocationUI();
    extern void RenderCurrentScene();
}