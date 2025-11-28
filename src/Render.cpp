#include "Render.hpp"
#include "GameData.hpp"

#define RAYLIB_WIN32_CONSOLE
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "main.hpp"
#include "raymath.h"
#include "GameData.hpp"

namespace Render
{
    namespace Textures
    {
        Texture T_mainmenu;
        Texture T_phone;
        Texture T_DG;
        Texture T_Title;

        void Load()
        {
            T_mainmenu = LoadTexture("assets/menu.bmp");
            T_phone = LoadTexture("assets/phone.bmp");
            T_DG = LoadTexture("assets/dg.bmp");
            T_Title = LoadTexture("assets/title.bmp");
        }

        void Unload()
        {
            UnloadTexture(T_mainmenu);
            UnloadTexture(T_phone);
            UnloadTexture(T_DG);
            UnloadTexture(T_Title);
        }
    }

    namespace Sounds
    {
        Sound Ring;
        Sound WifeDialogue;

        void Load()
        {
            Ring = LoadSound("assets/ring.mp3");
            WifeDialogue = LoadSound("assets/wifdialoguepeak.mp3");
        }

        void Unload()
        {
            UnloadSound(Ring);
            UnloadSound(WifeDialogue);
        }
    }

    namespace Fonts
    {
        void Load();
        void Unload();
    }

    namespace Music
    {
        void Load();
        void Unload();
    }

    bool rang = false;
    bool wif = false;
    bool lore = false;

    void RenderCurrentLocationUI()
    {
        switch (g_PlayerData.currentlocation)
        {
            case L_INTRO:
            {
                if (!lore)
                {
                    DrawTexturePro(Textures::T_phone,{0,0,(float)Textures::T_phone.width,(float)Textures::T_phone.height},{300,20,600,700},{0,0},0,WHITE);
                }else {
                    DrawTextPro(
                        GetFontDefault(),
                        "your wife doesnt want you home until youl get rid of this debt\nyoure in 10k debt and to beat this game you have to find a way to get rid of it\n(sorry for tts i cant voice act for shit)\npress space to continue",{20,300},{0,0},0,24,0.5f,WHITE
                    );
                    if (IsKeyPressed(KEY_SPACE))
                    {
                        g_PlayerData.currentlocation = L_FACTORY;
                    }
                }
                break;
            }
            case L_ABANDONED_HOUSE:
            {
                break;
            }
            case L_ALLEY:
            {
                break;
            }
            case L_BAR:
            {
                break;
            }
            case L_DISCORD_MOD_EASTEREGG:
            {
                break;
            }
            case L_DOWNTOWN:
            {
                break;
            }
            case L_FACTORY:
            {
                break;
            }
            case L_KULT:
            {
                break;
            }

        default:
            break;
        }
        return;
    }

    void RenderCurrentLocation()
    {
        switch (g_PlayerData.currentlocation)
        {
            case L_INTRO:
            {
                if (!rang)
                {
                    PlaySound(Sounds::Ring);
                    rang = true;
                }else {
                    if (!IsSoundPlaying(Sounds::Ring))
                    {
                        if (!wif)
                        {
                            PlaySound(Sounds::WifeDialogue);
                            wif = true;
                        }else {
                            if (!IsSoundPlaying(Sounds::WifeDialogue))
                            {
                                lore = true;
                            }
                        }
                    }
                }
                break;
            }
            case L_ABANDONED_HOUSE:
            {
                break;
            }
            case L_ALLEY:
            {
                break;
            }
            case L_BAR:
            {
                break;
            }
            case L_DISCORD_MOD_EASTEREGG:
            {
                break;
            }
            case L_DOWNTOWN:
            {
                break;
            }
            case L_FACTORY:
            {
                break;
            }
            case L_KULT:
            {
                break;
            }

        default:
            break;
        }
        return;
    }

    void PrepUI()
    {
        GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
        GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, ColorToInt({30,30,30,255}));
        GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, ColorToInt({60,60,60,255}));
        GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, ColorToInt({20,20,20,255}));
        GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, ColorToInt(WHITE));
        GuiSetStyle(BUTTON, TEXT_COLOR_FOCUSED, ColorToInt(YELLOW));
        GuiSetStyle(BUTTON, TEXT_COLOR_PRESSED, ColorToInt(LIGHTGRAY));
        return;
    }

    void RenderUI()
    {
        switch (g_PlayerData.currentscene)
        {
            case Scenes::S_MAINMENU:
            {
                DrawTexturePro(Textures::T_mainmenu,{0,0,(float)Textures::T_mainmenu.width,(float)Textures::T_mainmenu.height},{0,0,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);

                DrawTexturePro(Textures::T_Title,{0,0,(float)Textures::T_Title.width,(float)Textures::T_Title.height},{20,20,300,150},{0,0},0,WHITE);

                Vector2 p1 = {20, 160};
                if (GuiButton({p1.x, p1.y, 80, 40}, "Play"))
                {
                    g_PlayerData.currentscene = Scenes::S_GAME;
                }

                Vector2 p2 = {120, 160};
                if (GuiButton({p2.x, p2.y, 80, 40}, "Credits"))
                {
                    g_PlayerData.currentscene = Scenes::S_CREDITS;
                }

                Vector2 p3 = {220, 160};
                if (GuiButton({p3.x, p3.y, 80, 40}, "Quit"))
                {
                    shouldclose = true;
                }

                DrawTexturePro(Textures::T_DG,{0,0,(float)Textures::T_DG.width,(float)Textures::T_DG.height},{20,500,700,300},{0,0},0,WHITE);

                break;
            }
            case Scenes::S_GAME:
            {
                RenderCurrentLocationUI();
                break;
            }
            case Scenes::S_GAMEOVER:
            {
                break;
            }
            case Scenes::S_CREDITS:
            {
                DrawTexturePro(Textures::T_mainmenu,{0,0,(float)Textures::T_mainmenu.width,(float)Textures::T_mainmenu.height},{0,0,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);

                Vector2 p1 = {20, 20};
                if (GuiButton({p1.x, p1.y, 80, 40}, "Go Back"))
                {
                    g_PlayerData.currentscene = Scenes::S_MAINMENU;
                }

                DrawTextPro(
                    GetFontDefault(),
                    "Programming : Shadowdev\nArt : Shadowdev\n\nTools :\nSmartTableDatabase, raylib, raygui",Vector2{20,100},{0,0},0,24,0.5f,BLACK
                );

                break;
            }
        default:
            break;
        }
        return;
        
    }

    void RenderCurrentScene()
    {
        switch (g_PlayerData.currentscene)
        {
            case Scenes::S_MAINMENU:
            {
                break;
            }
            case Scenes::S_GAME:
            {
                RenderCurrentLocation();
                break;
            }
            case Scenes::S_GAMEOVER:
            {
                break;
            }
            case Scenes::S_CREDITS:
            {
                break;
            }
        default:
            break;
        }
        return;
    }
}