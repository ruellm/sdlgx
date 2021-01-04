#include "resource.h"

using namespace sdlgx::resource;

ResourceManager* ResourceManager::m_instance = NULL;

ImageAsset::ImageAsset()
{
	path = NULL;
	id = RESOURCE_ID_NONE;
	groud_id = -1;
	img = NULL;
}
ImageAsset::~ImageAsset()
{
	if (img) {
		SDL_FreeSurface(img);
		img = NULL;
	}
}


ResourceManager::ResourceManager() :
	_thread(NULL), _currentList(NULL), _handler(NULL)
{
}


ResourceManager::~ResourceManager()
{
	EmptyResource();
}

void ResourceManager::EmptyResource()
{
	ImageResource* img = NULL;
	if (m_image_list.first(img))
	{
		do {
			SAFE_DELETE(img);
		} while (m_image_list.getNext(img));
	}

	m_image_list.makeEmpty();

	if (_thread)
	{
		int threadReturnValue = 0;
		SDL_WaitThread(_thread, &threadReturnValue);
	}
}
#if 0
void ResourceManager::LoadImages(ResourceDef list[],
	int count, IResourceHandler* handler)
{
	for (int i = 0; i < count; i++) {
		ImageResource* resource = new ImageResource();

		SDL_Surface* img = IMG_Load(list[i].path);
		if (img == NULL) {
			printf("Resource::LoadImages: Unable to load image %s\n", list[i].path);
			continue;
		}

		resource->id = list[i].id;
		resource->groud_id = list[i].group_id;
		resource->img = img;

		m_image_list.insert(resource);

		if (handler) {
			handler->OnResourceLoad(i);
		}
	}

}
#endif

ImageResource* ResourceManager::GetResource(short id)
{
	ImageResource* resource = NULL;
	if (m_image_list.first(resource))
	{
		do
		{
			if (resource->id == id)
			{
				return resource;
			}

		} while (m_image_list.getNext(resource));
	}

	return NULL;

}

SDL_Surface*
ResourceManager::GetImage(short id)
{
	ImageResource* resource = NULL;
	if (m_image_list.first(resource))
	{
		do
		{
			if (resource->id == id)
			{
				if (resource->defer) {
					return IMG_Load(resource->path);
				}
				else {
					return resource->img;
				}
			}

		} while (m_image_list.getNext(resource));
	}

	return NULL;
}


ResourceManager* 
ResourceManager::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new ResourceManager();
	return m_instance;
}

void ResourceManager::Cleanup()
{
	SAFE_DELETE(m_instance);
}

int ResourceLoaderThread(void* ptr)
{
	ResourceManager* instance = (ResourceManager*)ptr;
	instance->Load();
	return 0;
}

void ResourceManager::Load()
{
	for (int i = 0; i < _listCount; i++) {
		ImageResource* resource = new ImageResource();

		if (!_currentList[i].defer) {
			SDL_Surface* img = IMG_Load(_currentList[i].path);
			if (img == NULL) {
				printf("Resource::LoadImages: Unable to load image %s\n", _currentList[i].path);
				continue;
			}
			resource->img = img;
		}

		resource->id = _currentList[i].id;
		resource->groud_id = _currentList[i].group_id;
		resource->defer = _currentList[i].defer;

		int len = strlen(_currentList[i].path) + 1;
		resource->path = new char[len];
		strcpy(resource->path, _currentList[i].path);

		m_image_list.insert(resource);

		if (_handler) {
			_handler->OnResourceLoad(i);
		}
	}
}

void ResourceManager::LoadAsync(ResourceDef* list, int count, IResourceHandler* handler)
{
	_currentList = list;
	_listCount = count;
	_handler = handler;

	// Simply create a thread
	_thread = SDL_CreateThread(ResourceLoaderThread, "ResourceLoaderThrd", (void *)m_instance);
}

void ResourceManager::Free(short id)
{
	ImageResource* resource = NULL;
	if (m_image_list.first(resource))
	{
		do
		{
			if (resource->id == id)
			{
				m_image_list.remove(resource);
				SAFE_DELETE(resource);
			}

		} while (m_image_list.getNext(resource));
	}
}