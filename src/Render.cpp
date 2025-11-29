#include "Render.hpp"
#include "GameData.hpp"

#define RAYLIB_WIN32_CONSOLE
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "main.hpp"
#include "raymath.h"
#include "GameData.hpp"

#include "Utils.hpp"
#include "Logger.hpp"

namespace Render
{
    namespace Textures
    {
        Texture T_mainmenu;
        Texture T_phone;
        Texture T_DG;
        Texture T_Title;

        Texture T_Map;
        Texture T_Map_Overlay;

        Texture T_Factory;

        void Load()
        {
            T_mainmenu = LoadTexture("assets/menu.bmp");
            T_phone = LoadTexture("assets/phone.bmp");
            T_DG = LoadTexture("assets/dg.bmp");
            T_Title = LoadTexture("assets/title.bmp");
            T_Factory = LoadTexture("assets/factory.bmp");
            T_Map = LoadTexture("assets/map.bmp");
            T_Map_Overlay = LoadTexture("assets/veryrealisticmap.bmp");
        }

        void Unload()
        {
            UnloadTexture(T_mainmenu);
            UnloadTexture(T_phone);
            UnloadTexture(T_DG);
            UnloadTexture(T_Title);
            UnloadTexture(T_Factory);
            UnloadTexture(T_Map);
            UnloadTexture(T_Map_Overlay);
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

    bool mapisopen = false;

    bool rang = false;
    bool wif = false;
    bool lore = false;

    void RenderCurrentLocationUI()
    {
        Vector2 mp = GetMousePosition();

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

        Rectangle map_rec = {20,700,64,64};

        if (g_PlayerData.currentlocation != L_INTRO)
        {
            if (!mapisopen)
            {
                DrawTexturePro(
                    Textures::T_Map,
                    {0,0,(float)Textures::T_Map.width,(float)Textures::T_Map.height},map_rec,{0,0},0,WHITE
                );

                switch (Utils::InvisibleButton(map_rec,"Map"))
                {
                    case Utils::Clicked:
                    {
                        mapisopen = true;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("open Map",24),24,YELLOW);
                        DrawText("open Map",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }
            }else 
            {
                DrawTexturePro(
                    Textures::T_Map_Overlay,
                    {0,0,(float)Textures::T_Map_Overlay.width,(float)Textures::T_Map_Overlay.height},
                    {0,0,(float)GetScreenWidth(),(float)GetScreenHeight()},
                    {0,0},
                    0,
                    WHITE
                );

                Rectangle Kult = {21.000000,7.000000,29.000000,23.000000};

                switch (Utils::InvisibleButton(Kult,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_KULT;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to Kult",24),24,YELLOW);
                        DrawText("Go to Kult",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle Factory = {134.000000,618.000000,5.000000,31.000000};

                switch (Utils::InvisibleButton(Factory,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_FACTORY;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to work",24),24,YELLOW);
                        DrawText("Go to work",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle GamblingDen = {984.000000,204.000000,20.000000,13.000000};

                switch (Utils::InvisibleButton(GamblingDen,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_GAMBLING_DEN;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to casino",24),24,YELLOW);
                        DrawText("Go to casino",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle AbandonedHouse = {469.000000,418.000000,22.000000,19.000000};

                switch (Utils::InvisibleButton(AbandonedHouse,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_ABANDONED_HOUSE;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to abandoned house",24),24,YELLOW);
                        DrawText("Go to abandoned house",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle Bar = {842.000000,599.000000,26.000000,12.000000};

                switch (Utils::InvisibleButton(Bar,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_BAR;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to Bar",24),24,YELLOW);
                        DrawText("Go to Bar",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle Alley = {1138.000000,673.000000,24.000000,17.000000};

                switch (Utils::InvisibleButton(Alley,""))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_ALLEY;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go to an alley",24),24,YELLOW);
                        DrawText("Go to an alley",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle Back = {GetScreenWidth() - 100,740,80,40};

                if (GuiButton(Back,"Back"))
                {
                    mapisopen = false;
                }
            }
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
                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_Factory,{0,0,(float)Textures::T_Factory.width,(float)Textures::T_Factory.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);
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