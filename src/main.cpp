#define RAYLIB_WIN32_CONSOLE
#include "raylib.h"

#define UNICODE
#include "boxer.h"
#include "GameData.hpp"
#include "main.hpp"
#include "Render.hpp"

#include "Logger.hpp"

#include "Utils.hpp"

#include "Input.hpp"

#include "MiniGames.hpp"

Camera2D g_Camera = { 0 };

unsigned int Warning()
{
	const char* msg =
	    "cs\n"
	    "tahle hra je minena jako parodie realneho zivota.\n"
	    "pokud si myslis, ze se nastves kvuli tehle hre, tak to neni muj problem.\n"
	    "\n"
	    "en\n"
	    "this game is meant as a parody of real life.\n"
	    "if you think you'll get mad over this game, then that's not my problem.\n"
	    "\n"
	    "cs\n"
	    "chces pokracovat?\n"
	    "en\n"
	    "do you want to continue?\n"
	    "\n"
	    "inspirovano serii ZNK\n"
	    "inspired by the ZNK series";

	boxer::Selection response = boxer::show(
	    msg,
	    "Varovani / Warning",
	    boxer::Style::Warning,
	    boxer::Buttons::YesNo
	);

    switch (response)
    {
        case boxer::Selection::Yes: return 6;
        case boxer::Selection::No: return 7;
        default: return 7;
    }
}

int main()
{
	SAVESYSTEM::LoadGame();

	if (!g_PlayerData.sawWarning)
	{
		unsigned int res = Warning();
		if (res == 7)
			return -1;
		g_PlayerData.sawWarning = true;
	}

	debug = true;

    if (g_PlayerData.fullscreen)
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);
	}else
	{
		SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
	}
	
    InitWindow(1280, 800, " ");
	SetTargetFPS(24);

	SetExitKey(0);

	g_Camera.target = { 0.0f, 0.0f }; 
	g_Camera.offset = { 1280.0f / 2.0f, 800.0f / 2.0f };
	g_Camera.rotation = 0.0f;
	g_Camera.zoom = 1.0f;

	InitAudioDevice();

	Render::Textures::Load();
	Render::Sounds::Load();
	Render::_Music::Load();

	Render::PrepUI();

    while (!WindowShouldClose() && !shouldclose)
    {
        BeginDrawing();
        BeginMode2D(g_Camera);
		ClearBackground(BLACK);
		
		Render::RenderCurrentScene();
		
		EndMode2D();

		Render::RenderUI();

		Minigames::RenderCurrentMinUI();
		
		Logger::RenderLogger();

		UpdateMusicStream(Render::_Music::menutheme);
		UpdateMusicStream(Render::_Music::gameambience);

		if (g_PlayerData.currentscene != Scenes::S_GAME)
		{
		    if (!IsMusicStreamPlaying(Render::_Music::menutheme))
		        PlayMusicStream(Render::_Music::menutheme);
		
		    StopMusicStream(Render::_Music::gameambience);
		}
		else
		{
		    if (!IsMusicStreamPlaying(Render::_Music::gameambience))
		        PlayMusicStream(Render::_Music::gameambience);
		
		    StopMusicStream(Render::_Music::menutheme);
		}

		if (debug)
		{
			Utils::RenderMousePos();
		}

		Input::DoInput();

        EndDrawing();
    }

	SAVESYSTEM::SaveGame();

	Render::Textures::Unload();
	Render::Sounds::Unload();
	Render::_Music::Unload();

	CloseAudioDevice();

    CloseWindow();
    return 0;
}
