#include "MiniGames.hpp"

#include "Logger.hpp"

#include "raylib.h"
#include "Render.hpp"

#include "Utils.hpp"

#include "GameData.hpp"

#include <limits.h>

#include <string>

#include <cmath>

#include "raygui.h"
#include <vector>

namespace Minigames
{
    namespace Data
    {
        std::vector<Vector2> balllist = {};
    }

    Minigames_e CurrentMinigame = _None;

    float timer0 = 1;

    float timescale = 1;

    void Work()
    {
        if (timer0 > 0)
        {
            timer0 = timer0 - GetFrameTime();
            for (auto& i : Data::balllist)
            {
                i.y = i.y + (100 * timescale) * GetFrameTime();
            }
            timescale = Utils::Clamp(timescale + GetFrameTime() * 0.1f,1,10);
        }else {
            timer0 = 1;
            Data::balllist.push_back(Vector2{(float)GetRandomValue(200,800),100});
        }

        Rectangle clip = { 200, 100, 800, 600 };

        if (GuiButton({(float)GetScreenWidth() - 100,(float)GetScreenHeight() - 100,80,40},"Back"))
        {
            CurrentMinigame = _None;
            Data::balllist = {};
            timescale = 1;
            return;
        }

        BeginScissorMode((int)clip.x, (int)clip.y, (int)clip.width, (int)clip.height);

        DrawTexturePro(Render::Textures::T_Factory_Background,{0,0,(float)Render::Textures::T_Factory_Background.width,(float)Render::Textures::T_Factory_Background.height},clip,{0,0},0,WHITE);

        {
            Rectangle box = {
                Utils::Clamp(
                    GetMousePosition().x - (Render::Textures::T_Box.width * 0.25f * 0.5f),
                    clip.x,
                    clip.x + clip.width - (Render::Textures::T_Box.width * 0.25f)
                ),
                600,
                Render::Textures::T_Box.width * 0.25f,
                Render::Textures::T_Box.height * 0.25f
            };

            DrawTexturePro(
                Render::Textures::T_Box,
                { 0,0,(float)Render::Textures::T_Box.width,(float)Render::Textures::T_Box.height },
            
                {
                    box.x,
                    600,
                    Render::Textures::T_Box.width * 0.25f,
                    Render::Textures::T_Box.height * 0.25f
                },
            
                {0,0},
                0,
                WHITE
            );

            for (int i = 0; i < Data::balllist.size(); i++)
            {
                if (Data::balllist[i].y > clip.height + clip.y)
                {
                    CurrentMinigame = _None;
                    timescale = 1;
                }

                Vector2& b = Data::balllist[i];

                DrawCircle(b.x, b.y, 20, RED);

                float closestX = Utils::Clamp(b.x, box.x, box.x + box.width);
                float closestY = Utils::Clamp(b.y, box.y, box.y + box.height);
            
                float dx = b.x - closestX;
                float dy = b.y - closestY;
            
                if (dx * dx + dy * dy <= 20 * 20)
                {
                    g_PlayerData.cash += 1;
                    PlaySound(Render::Sounds::select);
                
                    Data::balllist.erase(Data::balllist.begin() + i);
                    i--;
                }
            }
        }

        EndScissorMode();

        return;
    }

    void SlotsUI()
    {
        Rectangle mp = {GetMousePosition().x,GetMousePosition().y,4,4};

        Rectangle slotshitbox = {300,50,600,700};

        if (IsSoundPlaying(Render::Sounds::Gambaspin))
        {
            DrawTexturePro(
                Render::Textures::T_Slots2,
                {0,0,(float)Render::Textures::T_Slots2.width,(float)Render::Textures::T_Slots2.height},
                slotshitbox,
                {0,0},
                0,
                WHITE
            );
        }
        else 
        {
            DrawTexturePro(
                Render::Textures::T_Slots1,
                {0,0,(float)Render::Textures::T_Slots1.width,(float)Render::Textures::T_Slots1.height},
                slotshitbox,
                {0,0},
                0,
                WHITE
            );
        }

        switch (Utils::InvisibleButton(slotshitbox))
        {
            case Utils::Hovering:
            {
                DrawRectangle(mp.x,mp.y,MeasureText("Spin!",24),24,YELLOW);
                DrawText("Spin!",mp.x,mp.y,24,BLACK);
                break;
            }
            case Utils::Clicked:
            {
                if (g_PlayerData.cash > 0 && g_PlayerData.cash - 10 > 0)
                {
                    if (!IsSoundPlaying(Render::Sounds::Gambaspin))
                    {
                        PlaySound(Render::Sounds::Gambaspin);

                        SetRandomSeed(GetTime());
                        if (GetRandomValue(1,2) == 2)
                        {
                            g_PlayerData.cash = g_PlayerData.cash * 2;
                            Logger::Log("youve won (your money was doubled)");
                        }else {
                            auto a = Utils::Clamp(g_PlayerData.cash / 2,10,_I32_MAX);
                            g_PlayerData.cash = g_PlayerData.cash - a;
                            Logger::Log("you lost youve lost " + std::to_string(a) + "$");
                        }
                    }
                }
                break;
            }
        default:
            break;
        }

        if (GuiButton({160,(float)GetScreenHeight() - 100,80,40},"Close"))
        {
            CurrentMinigame = _None;
        }

        return;
    }
    void Baggies_weed()
    {
        return;
    }

    int bscore = 0;

    void Baggies_heroine()
    {
        Rectangle clip = { 200, 100, 800, 600 };

        if (GuiButton({ (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 100, 80, 40 }, "Back"))
        {
            CurrentMinigame = _None;
            g_PlayerData.cash = g_PlayerData.cash + bscore * 2;
            bscore = 0;
            return;
        }

        static Rectangle heroine = { 0,0,0,0 };
        static bool spawned = false;

        if (!spawned)
        {
            float w = Render::Textures::T_heroine.width * 0.25f;
            float h = Render::Textures::T_heroine.height * 0.25f;

            heroine.width = w;
            heroine.height = h;

            heroine.x = GetRandomValue((int)clip.x, (int)(clip.x + clip.width - w));
            heroine.y = GetRandomValue((int)clip.y, (int)(clip.y + clip.height - h));

            spawned = true;
        }

        BeginScissorMode((int)clip.x, (int)clip.y, (int)clip.width, (int)clip.height);

        DrawTexturePro(
            Render::Textures::T_table,
            {0,0,(float)Render::Textures::T_table.width,(float)Render::Textures::T_table.height},
            clip,
            {0,0},
            0,
            WHITE
        );

        DrawTexturePro(
            Render::Textures::T_heroine,
            {0,0,(float)Render::Textures::T_heroine.width,(float)Render::Textures::T_heroine.height},
            heroine,
            {0,0},
            0,
            WHITE
        );

        float bw = Render::Textures::T_baggie.width * 0.25f;
        float bh = Render::Textures::T_baggie.height * 0.25f;

        Rectangle bag = {
            Utils::Clamp(GetMousePosition().x - bw * 0.5f, clip.x, clip.x + clip.width  - bw),
            Utils::Clamp(GetMousePosition().y - bh * 0.5f, clip.y, clip.y + clip.height - bh),
            bw,
            bh
        };

        DrawTexturePro(
            Render::Textures::T_baggie,
            {0,0,(float)Render::Textures::T_baggie.width,(float)Render::Textures::T_baggie.height},
            bag,
            {0,0},
            0,
            WHITE
        );

        if (CheckCollisionRecs(bag, heroine))
        {
            if (!IsSoundPlaying(Render::Sounds::plastic))
            {
                if (IsMouseButtonDown(0))
                {
                    PlaySound(Render::Sounds::plastic);
                    bscore++;

                    float w = heroine.width;
                    float h = heroine.height;

                    heroine.x = GetRandomValue((int)clip.x, (int)(clip.x + clip.width - w));
                    heroine.y = GetRandomValue((int)clip.y, (int)(clip.y + clip.height - h));

                    SetRandomSeed(GetTime());
                    if (GetRandomValue(1,3) == 3)
                    {
                        auto a = GetRandomValue(10,30);
                        Logger::Log("your boss has given you an bonus of : " + std::to_string(a) + "$");
                    }
                }
            }
        }

        EndScissorMode();

        DrawText(
            ("score : " + std::to_string(bscore)).c_str(),
            clip.x + 10,
            clip.y + 10,
            24,
            WHITE
        );
    }

    int cscore = 0;

    void Shoot_Cops()
    {
        BeginScissorMode(0, 0, GetScreenWidth(), GetScreenHeight());

        Rectangle clip = {0,400.000000,1200.000000,350.000000 };

        if (GuiButton({ (float)GetScreenWidth() - 100, (float)GetScreenHeight() - 100, 80, 40 }, "Back"))
        {
            CurrentMinigame = _None;
            g_PlayerData.cash = g_PlayerData.cash + cscore * 5;
            cscore = 0;
            return;
        }

        static Rectangle enemy = {0,0,0,0};
        static float timer = 0.0f;
        static bool alive = false;
        static int enemyType = 2;

        if (!alive)
        {
            enemyType = GetRandomValue(2, 4);

            float scale = 0.35f;
            Texture2D* tex = nullptr;

            if (enemyType == 2) tex = &Render::Textures::T_cop2;
            if (enemyType == 3) tex = &Render::Textures::T_cop3;
            if (enemyType == 4) tex = &Render::Textures::T_cop4;

            float w = tex->width * scale;
            float h = tex->height * scale;

            enemy.width = w;
            enemy.height = h;

            enemy.x = GetRandomValue((int)clip.x, (int)(clip.x + clip.width - w));
            enemy.y = Utils::Clamp( (float)GetRandomValue((int)clip.y, (int)(clip.y + clip.height - h)), clip.y, clip.y + clip.height - h );

            timer = 1.0f;
            alive = true;
        }

        if (alive)
        {
            timer -= GetFrameTime();
            if (timer <= 0.0f)
            {
                CurrentMinigame = _None;
                g_PlayerData.cash = g_PlayerData.cash + cscore * 5;
                cscore = 0;
                alive = false;
            }
        }

        BeginScissorMode((int)clip.x, (int)clip.y, (int)clip.width, (int)clip.height);

        if (alive)
        {
            Texture2D* tex = nullptr;

            if (enemyType == 2) tex = &Render::Textures::T_cop2;
            if (enemyType == 3) tex = &Render::Textures::T_cop3;
            if (enemyType == 4) tex = &Render::Textures::T_cop4;

            DrawTexturePro(
                *tex,
                {0,0,(float)tex->width,(float)tex->height},
                enemy,
                {0,0},
                0,
                WHITE
            );
        }

        if (alive && IsMouseButtonPressed(0))
        {
            Vector2 mp = GetMousePosition();

            if (CheckCollisionPointRec(mp, enemy))
            {
                alive = false;
                cscore++;

                PlaySound(Render::Sounds::Gunshot);

                switch (GetRandomValue(1,4))
                {
                    case 1:
                    {
                        if (!IsSoundPlaying(Render::Sounds::female_pain))
                        {
                            PlaySound(Render::Sounds::female_pain);
                        }
                        break;
                    }
                    case 2:
                    {
                        if (!IsSoundPlaying(Render::Sounds::male_pain))
                        {
                            PlaySound(Render::Sounds::male_pain);
                        }
                        break;
                    }
                default:
                    break;
                }
            }
        }

        EndScissorMode();

        DrawTexturePro(
            Render::Textures::T_gunviewmodel,
            {0,0,(float)Render::Textures::T_gunviewmodel.width,(float)Render::Textures::T_gunviewmodel.height},
            { GetMousePosition().x - 225, (float)GetScreenHeight() - 450, 450, 450 },
            {0,0},
            0,
            {255,255,255,128}
        );

        DrawText(
            ("score : " + std::to_string(cscore)).c_str(),
            20,
            20,
            28,
            WHITE
        );
    }

// Dealer path

    int score = 0;

    void Whip_followers()
    {
        Rectangle clip = { 200, 100, 800, 600 };

        if (GuiButton({(float)GetScreenWidth() - 100,(float)GetScreenHeight() - 100,80,40},"Back"))
        {
            CurrentMinigame = _None;
            g_PlayerData.cash = (int)g_PlayerData.cash + score * 2.5f;
            score = 0;
            return;
        }

        BeginScissorMode((int)clip.x, (int)clip.y, (int)clip.width, (int)clip.height);

        DrawTexturePro(
            Render::Textures::T_basement,
            {0,0,(float)Render::Textures::T_basement.width,(float)Render::Textures::T_basement.height},
            clip,
            {0,0},
            0,
            WHITE
        );

        float scale = 0.5f;

        float w = Render::Textures::T_standing_male_3.width * scale;
        float h = Render::Textures::T_standing_male_3.height * scale;

        Rectangle dst = {
            clip.x + (clip.width - w) * 0.5f,
            clip.y + clip.height - h,
            w,
            h
        };

        DrawTexturePro(
            Render::Textures::T_standing_male_3,
            {0,0,(float)Render::Textures::T_standing_male_3.width,(float)Render::Textures::T_standing_male_3.height},
            dst,
            {0,0},
            0,
            {128,128,128,255}
        );

        Rectangle knife = {
                Utils::Clamp(
                    GetMousePosition().x - (Render::Textures::T_knife.width * 0.25f * 0.5f),
                    clip.x,
                    clip.x + clip.width - (Render::Textures::T_knife.width * 0.25f)
                ),
                Utils::Clamp(
                    GetMousePosition().y - (Render::Textures::T_knife.height * 0.25f * 0.5f),
                    clip.y,
                    clip.y + clip.height - (Render::Textures::T_knife.height * 0.25f)
                ),
                Render::Textures::T_knife.width * 0.25f,
                Render::Textures::T_knife.height * 0.25f
            };

        DrawTexturePro(
            Render::Textures::T_knife,
            { 0,0,(float)Render::Textures::T_knife.width,(float)Render::Textures::T_knife.height },
            knife,
            { knife.width * 0.5f, knife.height * 0.5f }, // proper center pivot
            0,
            WHITE
        );

        if (IsMouseButtonDown(0))
        {
            if (!IsSoundPlaying(Render::Sounds::stab) && !IsSoundPlaying(Render::Sounds::male_pain))
            {
                score = score + 1;
                PlaySound(Render::Sounds::stab);
                SetSoundVolume(Render::Sounds::male_pain,0.3f);
                SetRandomSeed(GetTime());
                SetSoundPitch(Render::Sounds::male_pain,GetRandomValue(-0.7f,1.1f));
                PlaySound(Render::Sounds::male_pain);
                if (GetRandomValue(1,3) == 3)
                {
                    auto a = GetRandomValue(50,100);
                    Logger::Log("tommy gave you a bonus of " + std::to_string(a) + "$");
                    g_PlayerData.cash = g_PlayerData.cash + a;
                }
            }
        }

        DrawTextPro(
            GetFontDefault(),
            ("score : " + std::to_string(score)).c_str(),
            {clip.x,clip.y},
            {0,0},
            0,
            24,
            0.5f,
            WHITE
        );

        EndScissorMode();
    }



    void RenderCurrentMinUI()
    {
        switch (CurrentMinigame)
        {
            case Minigames_e::_Slots:
            {
                ::Minigames::SlotsUI();
                break;
            }
            case Minigames_e::_Whip_followers:
            {
                ::Minigames::Whip_followers();
                break;
            }
            case Minigames_e::_Baggies_heroine:
            {
                ::Minigames::Baggies_heroine();
                break;
            }
            case Minigames_e::_Baggies_weed:
            {
                ::Minigames::Baggies_weed();
                break;
            }
            case Minigames_e::_Shoot_cops:
            {
                ::Minigames::Shoot_Cops();
                break;
            }
            case Minigames_e::_None:
            {
                break;
            }
            case Minigames_e::_Work:
            {
                Work();
                break;
            }
            default:
            {
                Logger::Log("mini game not defined");
                break;
            }
        }
        return;
    }
}