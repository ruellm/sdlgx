#include "Graphics.h"
#include "font.h"

using namespace sdlgx::core;
using namespace sdlgx::scene;

SDL_mutex* Graphics::_mutex = NULL;

Graphics::Graphics() :
	m_window(NULL), 
	m_renderer(NULL), _resize(false),
	_backBuffer(NULL)
{
	memset(&m_setup, 0, sizeof(GraphicsSetup));
}


Graphics::~Graphics()
{
}

void Graphics::Initialize(const struct GraphicsSetup& setup)
{	
	InitSDL(setup);
	InitIMG();
	InitTTF();

	_mutex = SDL_CreateMutex();
}

void Graphics::Cleanup()
{
	// free backbuffer
	SDL_DestroyTexture(_backBuffer);
	_backBuffer = NULL;

	//shutdown IMG Utility library
	IMG_Quit();

	//Shutdow TTF library
	TTF_Quit();

	//Destroy Renderer
	SDL_DestroyRenderer(m_renderer);

	//Destroy window
	SDL_DestroyWindow(m_window);

	//Quit SDL subsystems
	SDL_Quit();

	SDL_DestroyMutex(_mutex);
}

void Graphics::InitSDL(const struct GraphicsSetup& setup)
{
	m_setup.width = setup.width;
	m_setup.height = setup.height;
	m_setup.full_screen = setup.full_screen;
	m_setup.window_title = setup.window_title;
	m_setup.logical_width = setup.logical_width;
	m_setup.logical_height = setup.logical_height;

	_nativeSize.x = 0;
	_nativeSize.y = 0;
	_nativeSize.w = m_setup.logical_width;
	_nativeSize.h = m_setup.logical_height;

	_newWindowSize.x = 0;
	_newWindowSize.y = 0;
	_newWindowSize.w = m_setup.width;
	_newWindowSize.h = m_setup.width;

	_scaleRatioW = 1.0f;
	_scaleRatioH = 1.0f;

	_resize = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
		int width = setup.width;
		int height = setup.height;
		SDL_DisplayMode current;

		if (setup.full_screen) {

			flags |= SDL_WINDOW_FULLSCREEN;
			SDL_GetCurrentDisplayMode(0, &current);

			width = current.w;
			height = current.h;
		}

		// Get current display mode of all displays.
		for (int i = 0; i < SDL_GetNumVideoDisplays(); ++i) {

			int should_be_zero = SDL_GetCurrentDisplayMode(i, &current);

			if (should_be_zero != 0)
				// In case of error...
				SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());

			else
				// On success, print the current display mode.
				SDL_Log("CURRENT Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);

			
			int dm = SDL_GetNumDisplayModes(i);
			for (int z = 0; z < dm;z++) {
				int result = SDL_GetDisplayMode(i, z, &current);
				SDL_Log("Display #%d: mode %d, current display mode is %dx%dpx @ %dhz.", i, dm, current.w, current.h, current.refresh_rate);
			}

		}
		
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

		//Set the scaling quality to linear(1), nearest pixel(0), best(2)--only direct3D
#if 0
		if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") < 0)
		{
			printf("Failed to set Render Scale Quality\n");
		}
#endif
		//Create window
		m_window = SDL_CreateWindow(setup.window_title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width, height, flags);

		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
		}


		//Similarly, you must use SDL_TEXTUREACCESS_TARGET when you create the texture
		_backBuffer = SDL_CreateTexture(m_renderer,
			SDL_GetWindowPixelFormat(m_window),
			SDL_TEXTUREACCESS_TARGET,
			m_setup.logical_width,
			m_setup.logical_height);

	}


	if (_nativeSize.w != _newWindowSize.w || 
		_nativeSize.h != _newWindowSize.h)
	{
		Resize();
	}
}

void Graphics::InitIMG()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}
}

void Graphics::InitTTF()
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
}

void Graphics::Resize()
{
	int w, h;

	printf("\nResizing buffers...");
	SDL_GetWindowSize(m_window, &w, &h);

	_scaleRatioW = (float)_nativeSize.w / (float)w;
	_scaleRatioH = (float)_nativeSize.h / (float)h;  //The ratio from the native size to the new size

	_newWindowSize.w = w;
	_newWindowSize.h = h;

	//In order to do a resize, you must destroy the back buffer. Try without it, it doesn't work
/*	SDL_DestroyTexture(_backBuffer);
	_backBuffer = SDL_CreateTexture(m_renderer,
		SDL_GetWindowPixelFormat(m_window),
		SDL_TEXTUREACCESS_TARGET, //Again, must be created using this
		_nativeSize.w,
		_nativeSize.h);
*/
/*	SDL_Rect viewPort;
	SDL_RenderGetViewport(m_renderer, &viewPort);

	if (viewPort.w != _newWindowSize.w || viewPort.h != _newWindowSize.h)
	{
		//VERY IMPORTANT - Change the viewport over to the new size. It doesn't do this for you.
		SDL_RenderSetViewport(m_renderer, &_newWindowSize);
	}*/
}

void Graphics::Clear()
{
	SDL_SetRenderTarget(m_renderer, _backBuffer);
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer);
}

void Graphics::Present()
{
	if (_resize) //If a resize is neccessary, do so.
	{
		Resize();
		_resize = false;
	}

	SDL_SetRenderTarget(m_renderer, NULL);
	SDL_RenderCopy(m_renderer, _backBuffer, &_nativeSize, &_newWindowSize); //Render the backBuffer onto the																		//screen at (0,0)   
	SDL_RenderPresent(m_renderer);

	SDL_SetRenderTarget(m_renderer, _backBuffer); //Set the target back to the back buffer
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0);
	SDL_RenderClear(m_renderer); //Clear the back buffer


}

SDL_Surface* Graphics::GetWindowSurface()
{
	return SDL_GetWindowSurface(m_window);
}

int Graphics::LockMutex()
{
	return SDL_LockMutex(_mutex);
}

void Graphics::UnlockMutex()
{
	SDL_UnlockMutex(_mutex);
}

SDL_Renderer* Graphics::GetRenderer() 
{
	return m_renderer;
}

int Graphics::GetWidth()
{
	SDL_Surface* window = GetWindowSurface();
	return window->w;
}

int Graphics::GetHeight()
{
	SDL_Surface* window = GetWindowSurface();
	return window->h;
}

float Graphics::GetScaleRatioW()
{
	return _scaleRatioW;
}

float Graphics::GetScaleRatioH()
{
	return _scaleRatioH;
}

int Graphics::GetLogicalWidth()
{
	return m_setup.logical_width;
}

int Graphics::GetLogicalHeight()
{
	return m_setup.logical_height;
}