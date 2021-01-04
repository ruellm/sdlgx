#include "TestScene.h"
#include "resource.h"
#include "engine.h"
#include "transition_effects.h"
#include "font.h"

using namespace sdlgx::resource;
using namespace sdlgx::core;
using namespace sdlgx::scene;

TestScene::TestScene() 
	:State(1), resource_loaded(false)
{
}


TestScene::~TestScene()
{
}

void TestScene::OnLoad()
{

}

int resource_total = 0;
void TestScene::OnInitialize()
{
	static ResourceDef resource[] = {
		//{"images/blue.png",0,0,true},
		//{"images/background.png",1,0,true },
		//{"images/buy-button.png",2,0,true },
	//	{"images/buy-hover-button.png",3,0,true },
	//	{"images/top-button.png",4,0,true },
	//	{"images/top-button-hover.png",5,0,true },
	//	{"images/hearts-15fps.png", 6, 0,true },
	//	{"images/Back Button Idle.png", 7, 0,true },
	//	{"images/Back Button Aura.png", 8, 0,true },
	//	{ "images/Case File Big Box Line Drag.png", 9, 0,true },
	//	{ "images/Case File Drag Thumb.png", 10, 0,true },
	//	{ "images/Drop down text box.png", 11, 0,true },
	//	{ "images/Resolutuon Drop down Idle.png", 12, 0,true },
		//{ "images/Resolution Drop down Toggle.png", 13, 0,true },
		//{ "images/drop down aura.png", 14, 0,true },
		{ "images/pixel_test/background without bars.png", 14, 0,true },
		{ "images/pixel_test/pixel filter.png", 15, 0,true },
		{ "images/pixel_test/text box.png", 16, 0,true },
		{ "images/pixel_test/tom talk test.png", 17, 0,true },
	};

	resource_total = sizeof(resource) / sizeof(ResourceDef);
	ResourceManager::GetInstance()->LoadAsync(resource, resource_total,
		this);

	struct FontDefinitiion g_fonts[] = {
		{ "fonts/MyriadPro-Regular.ttf",0, 100 }
	};
	
	SDLGX_InitFontDef(g_fonts, 1);
}

int resource_count = 0;

void TestScene::OnUpdate(float elapsed)
{
	//if (!resource_loaded) return;
	if (resource_count >= resource_total)
	{
		// Change state in here
		Engine::GetInstance()->ChangeState(3, TRANSITION_FADE);
	}
}

void TestScene::OnDraw() 
{
	//if (!resource_loaded) return;
	//m_texture.Draw(0, 0);
}

void TestScene::OnClose()
{}

bool TestScene::OnEvent(SDL_Event* e)
{
	return State::OnEvent(e);
}

bool TestScene::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_SPACE) {
		Engine::GetInstance()->ChangeState(2, TRANSITION_FADE);
		return true;
	}
	return false;
}

void TestScene::OnResourceLoad(int index)
{
	resource_count++;
}