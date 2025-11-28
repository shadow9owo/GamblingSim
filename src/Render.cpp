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

    }

    namespace Sounds
    {

    }

    namespace Fonts
    {

    }

    namespace Music
    {
        
    }

    void RenderCurrentLocation()
    {
        return;
    }

    void RenderUI()
    {
        switch (g_PlayerData.currentscene)
        {
            case Scenes::S_MAINMENU:
            {
                DrawTextPro(
                    GetFontDefault(),
                    "Gambling simulator (demo)",
                    Vector2{20,20},
                    Vector2{0,0},
                    0,
                    32,
                    0.5f,
                    WHITE
                );

                Vector2 p1 = {20, 60};
                if (GuiButton({p1.x, p1.y, 80, 40}, "Play"))
                {
                    g_PlayerData.currentscene = Scenes::S_GAME;
                }

                Vector2 p2 = {120, 60};
                if (GuiButton({p2.x, p2.y, 80, 40}, "Credits"))
                {
                    g_PlayerData.currentscene = Scenes::S_CREDITS;
                }

                Vector2 p3 = {220, 60};
                if (GuiButton({p3.x, p3.y, 80, 40}, "Quit"))
                {
                    shouldclose = true;
                }

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