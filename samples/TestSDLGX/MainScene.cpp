#include "MainScene.h"
#include "engine.h"
#include "font.h"

using namespace sdlgx::core;
using namespace sdlgx::gui;
using namespace sdlgx::scene;

MainScene::MainScene() 
	: State(2)
{
}


MainScene::~MainScene()
{
	SAFE_DELETE(_uimanager);
	SAFE_DELETE(m_hello_world);
}


void MainScene::OnLoad()
{
	
}

void MainScene::OnInitialize()
{
	m_texture.LoadFromResource(1);
	
	_uimanager = new UIManager();
	button1.Load(2, 3);
	button1._x = 100;
	button1._y = 50;
	button1.SetID(0);
	button1.SetHandler(this);
	
	button2.Load(4, 5);
	button2._x = 100;
	button2._y = 200;
	button2.SetID(1);
	button2.SetHandler(this);

	//_uimanager->Add(&button1);
	//_uimanager->Add(&button2);

	backbutton.Load(7, 7);
	backbutton.SetGlowImage(8, 60);
	backbutton._x = 300;
	backbutton._y = 300;
	backbutton.SetID(2);
	backbutton.SetHandler(this);
	//_uimanager->Add(&backbutton);

	heart.LoadFromResource(6);
	heart.Set(10, 15, true);

	scrollbar.SetBarImage(9);
	scrollbar.SetThumbImage(10);
	scrollbar._x = 500;
	scrollbar._y = 100;
	//_uimanager->Add(&scrollbar);

	//-->uncomment the next 2 lines to this static font/text
	//	SDL_Color color = { 255,255,255 };
	//	m_hello_world = SDLGX_GetText("Hello world!", 0, 50, color);

	char values[][20] = {
		"item1",
		"item2",
		"item3",
		"item4",
	};

	combobox.Load(values, 4);
	combobox.SetCoordinates(10, 100);
	combobox.SetTextBoxImg(11);
	combobox.SetToggleButton(12, 13,14);
	_uimanager->Add(&combobox);
}

void MainScene::OnButtonClick(Button* b)
{
	printf("\nButton clicked %d", b->GetID());
}

void MainScene::OnUpdate(float elapsed)
{
	_uimanager->OnUpdate(elapsed);
	heart.OnUpdate(elapsed);

}

void MainScene::OnDraw()
{
	m_texture.Draw(0, 0);

	_uimanager->OnDraw();

//	heart.OnDraw(100, 300);

	//--> uncomment this for testing of wrapper function
	//SDL_Color color = {255,255,255};
	//SDLGX_DrawText(50, 10, "Hello world!", 0, 50,color);

	//-->uncomment this to this static font/text
	//m_hello_world->Draw(50, 10);
}

void MainScene::OnClose()
{}

bool MainScene::OnEvent(SDL_Event* e)
{
	return State::OnEvent(e);
}

bool MainScene::OnKeyDown(SDL_Keycode sym)
{
	if (sym == SDLK_ESCAPE) {
		Engine::GetInstance()->Shutdown();
		return true;
	}
	return false;
}
