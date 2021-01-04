#pragma once
#include "object_base.h"
#include "texture.h"
#include "Evidence.h"
#include "CustomEvent.h"

typedef enum IconBoxState
{
	ICONBOX_STATE_NONE = 0,
	ICONBOX_STATE_MOVING,
	ICONBOX_STATE_ZOOMING,
}ICONBOXSTATE;

#define ICONBOX_WIDTH	95 
#define ICONBOX_HEIGHT	95

class IconBox : public sdlgx::core::ObjectBase
{
public:
	IconBox();
	~IconBox();

	void Load(EvidenceType type);
	virtual void OnUpdate(float elapsed);
	virtual void OnDraw();

	void ZoomIn(int cx, int cy);
	void MoveTo(int x, int y);

	void SetEventHandler(ICustomEvent* h);
	EvidenceType GetType();

private:
	EvidenceType _type;
	ICONBOXSTATE _state;
	sdlgx::scene::Texture _texture;
	
	int _targetX;
	int _targetY;
	int _targetWidth;
	int _targetHeight;
	int _centerZoomX;
	int _centerZoomY;
	int _zoom_flag;
	int _dirX;
	int _dirY;


	void OnUpdateMoving(float elapsed);
	void OnUpdateZoom(float elapsed);

	ICustomEvent* _handler;
};