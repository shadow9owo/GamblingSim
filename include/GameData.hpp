#pragma once

#include <vector>

enum Locations
{
    L_INTRO,
    L_FACTORY,
    L_DOWNTOWN,
    L_BAR,
    L_ALLEY,
    L_ABANDONED_HOUSE,
    L_GAMBLING_DEN,
    L_KULT,
    L_DISCORD_MOD_EASTEREGG
};

enum Scenes
{
    S_MAINMENU,
    S_GAME,
    S_GAMEOVER,
    S_CREDITS
};

enum Items
{
    I_KNIFE,
    I_WALLET,
    I_PHONE,
    I_ID,
    I_BOOZE,
    I_CIGARETTES,
    I_DRUGS_HEROINE,
    I_FIRST_AID_KIT
};

struct locationstate
{
    bool visited = false;
    bool locked = false;
    Locations location = L_INTRO;
};

class PlayerData
{
    public:
        bool sawWarning = false;
        int health = 100;
        int debt = 100000;
        int cash = 50;
        std::vector<Items> inventory;
        std::vector<locationstate> locations;
        Scenes currentscene = S_MAINMENU;
        Locations currentlocation = L_INTRO;
};

extern PlayerData g_PlayerData;

extern bool shouldclose;

namespace SAVESYSTEM
{
    extern void SaveGame();
    extern void LoadGame();
}