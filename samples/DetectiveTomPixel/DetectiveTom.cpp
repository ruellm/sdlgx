// DetectiveTom.cpp : the entry point of the game.
// Created September 03, 2016
// Author: Ruell Magpayo <ruellm@yaho.com>

#include "engine.h"
#include "LoadingState.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "definitions.h"
#include "PreludeDialogState.h"

using namespace sdlgx::core;

int main(int argc, char *args[])
{
	Engine* engine = Engine::GetInstance();

	struct GraphicsSetup gfx;
	gfx.width = 960;
	gfx.height = 540;
	gfx.logical_width = 640;
	gfx.logical_height = 360;
	gfx.full_screen = false;
	gfx.window_title = "Detective Tom v0.0.1";

	engine->SetGraphicsSetings(gfx);
	engine->AddState((State*)new LoadingState());
	engine->AddState((State*)new MainMenuState());
	engine->AddState((State*)new GameState());

	// Game screen states
	engine->AddState((State*)new PreludeDialogState());
	engine->ChangeState(LOADING_STATE);
	engine->Run();

    return 0;
}

