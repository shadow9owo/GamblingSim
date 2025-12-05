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

#include "MiniGames.hpp"

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

        Texture T_scientologyhq;
        Texture T_standing_female_1;
        Texture T_standing_male_1;
        Texture T_standing_male_2;
        Texture T_standing_male_3;

        Texture T_casino;
        Texture T_alley;
        Texture T_abandonedhouse;

        Texture T_Factory;
        Texture T_Home;

        Texture T_Slots1;
        Texture T_Slots2;

        Texture T_Factory_Background;

        Texture T_Box;

        Texture T_scientologist;

        Texture T_basement;

        Texture T_knife;

        Texture T_table;

        Texture T_baggie;

        Texture T_heroine;

        Texture T_cop1;
        Texture T_cop2;
        Texture T_cop3;
        Texture T_cop4;

        Texture T_gunviewmodel;

        void Load()
        {
            T_mainmenu = LoadTexture("assets/menu.bmp");
            T_phone = LoadTexture("assets/phone.bmp");
            T_DG = LoadTexture("assets/dg.bmp");
            T_Title = LoadTexture("assets/title.bmp");
            T_Factory = LoadTexture("assets/factory.bmp");
            T_Map = LoadTexture("assets/map.bmp");
            T_Map_Overlay = LoadTexture("assets/veryrealisticmap.bmp");

            T_scientologyhq = LoadTexture("assets/scientologyhq.bmp");
            T_alley = LoadTexture("assets/alley.bmp");
            T_casino = LoadTexture("assets/casino.bmp");
            T_abandonedhouse = LoadTexture("assets/abandonedhouse.bmp");

            T_standing_male_1 = LoadTexture("assets/standingmale1.bmp");
            T_standing_male_2 = LoadTexture("assets/standingmale2.bmp");
            T_standing_male_3 = LoadTexture("assets/standingmale3.bmp");
            T_standing_female_1 = LoadTexture("assets/standingfemale1.bmp");

            T_Home = LoadTexture("assets/bar.bmp");

            T_Slots1 = LoadTexture("assets/slots1.bmp");
            T_Slots2 = LoadTexture("assets/slots2.bmp");

            T_Box = LoadTexture("assets/box.bmp");
            T_Factory_Background = LoadTexture("assets/factory_background.bmp");

            T_basement = LoadTexture("assets/basement.bmp"); 

            T_scientologist = LoadTexture("assets/scientologist.bmp");

            T_knife = LoadTexture("assets/knive.bmp");

            T_table = LoadTexture("assets/table.bmp");

            T_baggie = LoadTexture("assets/baggie.bmp");
            T_heroine = LoadTexture("assets/heroine.bmp");

            T_cop1 = LoadTexture("assets/cop1.bmp");

            //aim down
            T_cop2 = LoadTexture("assets/cop2.bmp");
            T_cop3 = LoadTexture("assets/cop3.bmp");
            T_cop4 = LoadTexture("assets/cop4.bmp");

            T_gunviewmodel = LoadTexture("assets/gunviewmodel.bmp");
        }

        void Unload()
        {
            UnloadTexture(T_mainmenu);
            UnloadTexture(T_phone);
            UnloadTexture(T_DG);
            UnloadTexture(T_Title);
            UnloadTexture(T_Map);
            UnloadTexture(T_Map_Overlay);

            UnloadTexture(T_scientologyhq);
            UnloadTexture(T_Factory);
            UnloadTexture(T_alley);
            UnloadTexture(T_casino);
            UnloadTexture(T_abandonedhouse);

            UnloadTexture(T_standing_male_1);
            UnloadTexture(T_standing_male_2);
            UnloadTexture(T_standing_male_3);
            UnloadTexture(T_standing_female_1);

            UnloadTexture(T_Box);
            UnloadTexture(T_Factory_Background);

            UnloadTexture(T_basement);
            UnloadTexture(T_scientologist);
            UnloadTexture(T_knife);

            UnloadTexture(T_table);
            UnloadTexture(T_heroine);
            UnloadTexture(T_baggie);

            UnloadTexture(T_cop1);
            UnloadTexture(T_cop2);
            UnloadTexture(T_cop3);
            UnloadTexture(T_cop4);

            UnloadTexture(T_gunviewmodel);
        }
    }

    namespace Sounds
    {
        Sound Ring;
        Sound WifeDialogue;
        Sound Gunshot;
        Sound Gambaspin;
        Sound plastic;
        Sound female_pain;
        Sound male_pain;
        Sound stab;
        Sound select;

        void Load()
        {
            Ring = LoadSound("assets/ring.mp3");
            WifeDialogue = LoadSound("assets/wifdialoguepeak.mp3");
            Gunshot = LoadSound("assets/gunshot.wav");
            Gambaspin = LoadSound("assets/spin.mp3");
            plastic = LoadSound("assets/plastic.wav");
            female_pain = LoadSound("assets/female_pain.mp3");
            male_pain = LoadSound("assets/male_pain.wav");
            stab = LoadSound("assets/knive.wav");
            select = LoadSound("assets/select.wav");
        }

        void Unload()
        {
            UnloadSound(Ring);
            UnloadSound(WifeDialogue);
            UnloadSound(Gunshot);
            UnloadSound(Gambaspin);
            UnloadSound(plastic);
            UnloadSound(female_pain);
            UnloadSound(male_pain);
            UnloadSound(stab);
            UnloadSound(select);
        }
    }

    namespace Fonts
    {
        void Load();
        void Unload();
    }

    namespace _Music
    {
        Music menutheme;
        Music gameambience;

        void Load()
        {
            menutheme = LoadMusicStream("assets/menutheme.mp3");
            gameambience = LoadMusicStream("assets/ambience.wav");
            return;
        }

        void Unload()
        {
            UnloadMusicStream(menutheme);
            UnloadMusicStream(gameambience);
            return;
        }
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
                        g_PlayerData.health = 100;
                        g_PlayerData.debt = 100000;
                        g_PlayerData.cash = 50;
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

                switch (Utils::InvisibleButton(map_rec))
                {
                    case Utils::Clicked:
                    {
                        Minigames::CurrentMinigame = Minigames::Minigames_e::_None;
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

                switch (Utils::InvisibleButton(Kult))
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

                switch (Utils::InvisibleButton(Factory))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_FACTORY;
                        mapisopen = false;
                        Minigames::Data::balllist = {};
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

                switch (Utils::InvisibleButton(GamblingDen))
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

                switch (Utils::InvisibleButton(AbandonedHouse))
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

                switch (Utils::InvisibleButton(Bar))
                {
                    case Utils::Clicked:
                    {
                        g_PlayerData.currentlocation = L_BAR;
                        mapisopen = false;
                        break;
                    }
                    case Utils::Hovering:
                    {
                        DrawRectangle(mp.x,mp.y,MeasureText("Go Home",24),24,YELLOW);
                        DrawText("Go Home",mp.x,mp.y,24,BLACK);
                        break;
                    }

                default:
                    break;
                }

                Rectangle Alley = {1138.000000,673.000000,24.000000,17.000000};

                switch (Utils::InvisibleButton(Alley))
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
        Vector2 mp = GetMousePosition();

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
                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_abandonedhouse,{0,0,(float)Textures::T_abandonedhouse.width,(float)Textures::T_abandonedhouse.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);
                
                Rectangle crackhead = {
                    GetScreenToWorld2D({593.000000,372.000000}, g_Camera).x,
                    GetScreenToWorld2D({593.000000,372.000000}, g_Camera).y,
                    150.000000,300.000000
                };

                Rectangle entrance = {
                    GetScreenToWorld2D({291.000000,360.000000}, g_Camera).x,
                    GetScreenToWorld2D({291.000000,360.000000}, g_Camera).y,
                    74.000000,171.000000
                };

                DrawTexturePro(
                    Render::Textures::T_standing_male_2,
                    {0,0,(float)Render::Textures::T_standing_male_2.width,(float)Render::Textures::T_standing_male_2.height},
                    crackhead,
                    {0,0},
                    0,
                    WHITE
                );

                auto a = GetScreenToWorld2D(mp,g_Camera);

                if (!mapisopen && Minigames::CurrentMinigame == Minigames::Minigames_e::_None)
                {
                    switch (Utils::InvisibleButton(crackhead,a))
                    {
                        case Utils::Clicked:
                        {
                            Logger::Log("hey wanna help us package our drugs we need hand and i see youre in debt");
                            Logger::Log("click on the door to start the job");
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("talk to the drug manifacturer",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "talk to the drug manifacturer",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }

                    switch (Utils::InvisibleButton(entrance,a))
                    {
                        case Utils::Clicked:
                        {
                            Minigames::CurrentMinigame = Minigames::Minigames_e::_Baggies_heroine;
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("start job",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "start job",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }
                }

                break;
            }
            case L_ALLEY:
            {
                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_alley,{0,0,(float)Textures::T_alley.width,(float)Textures::T_alley.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);
                
                auto a = GetScreenToWorld2D(mp,g_Camera);

                Rectangle work = {
                    GetScreenToWorld2D({767.000000,452.000000}, g_Camera).x,
                    GetScreenToWorld2D({767.000000,452.000000}, g_Camera).y,
                    217.000000,210.000000
                };

                if (!mapisopen && Minigames::CurrentMinigame == Minigames::Minigames_e::_None)
                {
                    DrawTexturePro(Render::Textures::T_cop1,
                        {0,0,(float)Render::Textures::T_cop1.width,(float)Render::Textures::T_cop1.height},
                        work,{0,0},0,WHITE);

                    switch (Utils::InvisibleButton(work,a))
                    {
                        case Utils::Clicked:
                        {
                            Minigames::CurrentMinigame = Minigames::Minigames_e::_Shoot_cops;
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("Start heat streak",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "Start heat streak",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }
                }

                break;
            }
            case L_BAR: //home
            {
                auto pos = GetScreenToWorld2D({0,0}, g_Camera);
                DrawTexturePro(
                    Textures::T_Home,
                    {0,0,(float)Textures::T_Home.width,(float)Textures::T_Home.height},
                    {pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},
                    {0,0},
                    0,
                    WHITE
                );

                Rectangle debtcollector = {
                    GetScreenToWorld2D({206.000000,337.000000}, g_Camera).x,
                    GetScreenToWorld2D({206.000000,337.000000}, g_Camera).y,
                    200.000000,300.000000
                };

                DrawTexturePro(
                    Render::Textures::T_standing_male_1,
                    {0,0,(float)Render::Textures::T_standing_male_1.width,(float)Render::Textures::T_standing_male_1.height},
                    debtcollector,
                    {0,0},
                    0,
                    WHITE
                );
            
                Rectangle entrance = {
                    GetScreenToWorld2D({530,331}, g_Camera).x,
                    GetScreenToWorld2D({530,331}, g_Camera).y,
                    134.0f,
                    246.0f
                };
                
                auto a = GetScreenToWorld2D(mp,g_Camera);

                if (!mapisopen)
                {
                    switch (Utils::InvisibleButton(entrance,a))
                    {
                        case Utils::Clicked:
                        {
                            if (g_PlayerData.debt <= 0)
                            {
                                g_PlayerData = {};
                                g_PlayerData.sawWarning = true;
                                SAVESYSTEM::SaveGame();
                                g_PlayerData.currentscene = S_CREDITS;    
                            }
                            else 
                            {
                                Logger::Log("you cant enter your home while still being in debt your wife would kill you.");
                            }
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("enter home",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "enter home",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }

                    switch (Utils::InvisibleButton(debtcollector,a))
                    {
                        case Utils::Clicked:
                        {
                            if (g_PlayerData.cash > 0)
                            {
                                int pay = g_PlayerData.cash > g_PlayerData.debt ? g_PlayerData.debt : g_PlayerData.cash;
                                g_PlayerData.debt -= pay;
                                g_PlayerData.cash -= pay;
                            }
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("pay back debt to the debt collector",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "pay back debt to the debt collector",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }
                }
            
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
                auto a = GetScreenToWorld2D(mp,g_Camera);

                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_Factory,{0,0,(float)Textures::T_Factory.width,(float)Textures::T_Factory.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);

                Rectangle work = {
                    GetScreenToWorld2D({767.000000,452.000000}, g_Camera).x,
                    GetScreenToWorld2D({767.000000,452.000000}, g_Camera).y,
                    217.000000,210.000000
                };
                if (!mapisopen)
                {
                    switch (Utils::InvisibleButton(work,a))
                    {
                        case Utils::Clicked:
                        {
                            Minigames::CurrentMinigame = Minigames::Minigames_e::_Work;
                            break;
                        }
                        case Utils::Hovering:
                        {
                            DrawRectangle(a.x, a.y,
                                          MeasureText("Work",24), 24, YELLOW);
                            DrawTextPro(
                                GetFontDefault(),
                                "Work",
                                {a.x,a.y},
                                {0,0},
                                0,
                                24,
                                0.5f,
                                BLACK
                            );
                            break;
                        }
                    
                        default:
                            break;
                    }
                }

                break;
            }
            case L_KULT:
            {
                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_scientologyhq,{0,0,(float)Textures::T_scientologyhq.width,(float)Textures::T_scientologyhq.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);

                auto a = GetScreenToWorld2D(mp,g_Camera);

                Rectangle tommy = {
                    GetScreenToWorld2D({141.000000,326.000000}, g_Camera).x,
                    GetScreenToWorld2D({141.000000,326.000000}, g_Camera).y,
                    216.000000,400.000000
                };

                Rectangle hqentrance = {
                    GetScreenToWorld2D({515.000000,291.000000}, g_Camera).x,
                    GetScreenToWorld2D({515.000000,291.000000}, g_Camera).y,
                    187.000000,281.000000
                };

                DrawTexturePro(Textures::T_scientologist,{0,0,(float)Textures::T_scientologist.width,(float)Textures::T_scientologist.height},tommy,{0,0},0,WHITE);
                
                if (Minigames::CurrentMinigame == Minigames::Minigames_e::_None)
                {
                    if (!mapisopen)
                    {
                        switch (Utils::InvisibleButton(tommy,a))
                        {
                            case Utils::Clicked:
                            {
                                Logger::Log("some of our k.. club members have been disobeying the rules we would appreciate your help");
                                Logger::Log("click on the door to start the job");
                                break;
                            }
                            case Utils::Hovering:
                            {
                                DrawRectangle(a.x, a.y,
                                              MeasureText("Talk to tommy",24), 24, YELLOW);
                                DrawTextPro(
                                    GetFontDefault(),
                                    "Talk to tommy",
                                    {a.x,a.y},
                                    {0,0},
                                    0,
                                    24,
                                    0.5f,
                                    BLACK
                                );
                                break;
                            }
                        
                            default:
                                break;
                        }
                    }

                    if (!mapisopen)
                    {
                        switch (Utils::InvisibleButton(hqentrance,a))
                        {
                            case Utils::Clicked:
                            {
                                Minigames::CurrentMinigame = Minigames::Minigames_e::_Whip_followers;
                                break;
                            }
                            case Utils::Hovering:
                            {
                                DrawRectangle(a.x, a.y,
                                              MeasureText("start job for mr tommy",24), 24, YELLOW);
                                DrawTextPro(
                                    GetFontDefault(),
                                    "start job for mr tommy",
                                    {a.x,a.y},
                                    {0,0},
                                    0,
                                    24,
                                    0.5f,
                                    BLACK
                                );
                                break;
                            }
                        
                            default:
                                break;
                        }
                    }
                }
                
                break;
            }
            case L_GAMBLING_DEN:
            {
                auto pos = GetScreenToWorld2D({0,0},g_Camera);
                DrawTexturePro(Textures::T_casino,{0,0,(float)Textures::T_casino.width,(float)Textures::T_casino.height},{pos.x,pos.y,(float)GetScreenWidth(),(float)GetScreenHeight()},{0,0},0,WHITE);

                Rectangle entrance = {
                    GetScreenToWorld2D({67.000000,226.000000}, g_Camera).x,
                    GetScreenToWorld2D({67.000000,226.000000}, g_Camera).y,
                    1096.000000,425.000000
                };
                
                auto a = GetScreenToWorld2D(mp,g_Camera);

                if (!mapisopen)
                {
                    if (Minigames::CurrentMinigame != Minigames::Minigames_e::_Slots)
                    {
                        switch (Utils::InvisibleButton(entrance,a))
                        {
                            case Utils::Clicked:
                            {
                                if (g_PlayerData.cash > 0)
                                {
                                    Minigames::CurrentMinigame = Minigames::Minigames_e::_Slots;
                                }
                                else 
                                {
                                    Logger::Log("you cant gamble without money.");
                                }
                                break;
                            }
                            case Utils::Hovering:
                            {
                                DrawRectangle(a.x, a.y,
                                              MeasureText("Open slots UI",24), 24, YELLOW);
                                DrawTextPro(
                                    GetFontDefault(),
                                    "Open slots UI",
                                    {a.x,a.y},
                                    {0,0},
                                    0,
                                    24,
                                    0.5f,
                                    BLACK
                                );
                                break;
                            }
                        
                            default:
                                break;
                        }
                    }
                }

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
                if (g_PlayerData.currentlocation != L_INTRO)
                {
                DrawRectanglePro(
                    {
                        (float)GetScreenWidth() - (
                            (float)std::max(
                                MeasureText(("money : " + std::to_string(g_PlayerData.cash) + "$").c_str(), 24),
                                MeasureText(("debt : " + std::to_string(g_PlayerData.debt) + "$").c_str(), 24)
                            ) + 40
                        ),
                        20,
                        (float)std::max(
                            MeasureText(("money : " + std::to_string(g_PlayerData.cash) + "$").c_str(), 24),
                            MeasureText(("debt : " + std::to_string(g_PlayerData.debt) + "$").c_str(), 24)
                        ) + 40,
                        60
                    },
                    {0,0},
                    0,
                    BLACK
                );
            
                DrawTextPro(
                    GetFontDefault(),
                    ("money : " + std::to_string(g_PlayerData.cash) + "$").c_str(),
                    {
                        (float)GetScreenWidth() - (
                            (float)std::max(
                                MeasureText(("money : " + std::to_string(g_PlayerData.cash) + "$").c_str(), 24),
                                MeasureText(("debt : " + std::to_string(g_PlayerData.debt) + "$").c_str(), 24)
                            ) + 20
                        ),
                        24
                    },
                    {0,0},
                    0,
                    24,
                    0.5f,
                    WHITE
                );
            
                DrawTextPro(
                    GetFontDefault(),
                    ("debt : " + std::to_string(g_PlayerData.debt) + "$").c_str(),
                    {
                        (float)GetScreenWidth() - (
                            (float)std::max(
                                MeasureText(("money : " + std::to_string(g_PlayerData.cash) + "$").c_str(), 24),
                                MeasureText(("debt : " + std::to_string(g_PlayerData.debt) + "$").c_str(), 24)
                            ) + 20
                        ),
                        48
                    },
                    {0,0},
                    0,
                    24,
                    0.5f,
                    WHITE
                );
                }            
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