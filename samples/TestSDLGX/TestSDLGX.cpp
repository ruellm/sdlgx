// TestSDLGX.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "TestScene.h"
#include "MainScene.h"
#include "PixelTestState.h"

using namespace sdlgx::core;

int main(int argc, char *args[])
{
	Engine* engine = Engine::GetInstance();

	struct GraphicsSetup gfx;
	gfx.width = 640;
	gfx.height = 360;
	gfx.logical_width = 640;
	gfx.logical_height = 360;
	gfx.full_screen = false;
	gfx.window_title = "SDL Game Extension v1";

	engine->SetGraphicsSetings(gfx);
	engine->AddState((State*)new TestScene());
	//engine->AddState((State*) new MainScene());
	engine->AddState((State*) new PixelTestState());
	engine->Run();

	return 0;
}

