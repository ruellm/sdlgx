#pragma once
#include "sdlgx_common.h"
#include "texture.h"
#include "link_list.h"

#include "SDL_thread.h"

namespace sdlgx {
	namespace resource {

		#define RESOURCE_ID_NONE (-1)

		typedef struct ResourceDefinition {
			char* path;
			short id;
			short group_id;
			bool defer;
		}ResourceDef;

		typedef struct SDLGX_API 
		ImageAsset {
			char* path;
			short id;
			short groud_id;
			bool defer;

			//sdlgx::scene::Texture* img;
			SDL_Surface* img;

			ImageAsset();
			~ImageAsset();

		}ImageResource;

		class IResourceHandler
		{
		public:
			virtual void OnResourceLoad(int) = 0;
		};


		class SDLGX_API ResourceManager
		{
		public:
			~ResourceManager();

			void LoadAsync(ResourceDef* list, int count, IResourceHandler* handler);
		//	void LoadImages(ResourceDef list[], int count, IResourceHandler* handler);
			void Load();
			void EmptyResource();
			void Free(short id);
			SDL_Surface* GetImage(short id);
			ImageResource* GetResource(short id);
			static ResourceManager* GetInstance();
			static void Cleanup();

		private:
			ResourceManager();
			sdlgx::common::LinkedList<ImageResource*> m_image_list;

			static ResourceManager* m_instance;			
			ResourceDef*_currentList;
			int _listCount;
			IResourceHandler* _handler;
			SDL_Thread* _thread;
		};
	}
}

