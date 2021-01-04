#include "object_base.h"

using namespace sdlgx::core;

ObjectBase::ObjectBase() 
	: _visible(true), _width(0), _height(0), _x(0), _y(0)
{
}


ObjectBase::~ObjectBase()
{
}

void ObjectBase::SetCoordinates(float x, float y)
{
	_x = x;
	_y = y;
}

int ObjectBase::GetWidth()
{
	return _width;
}

int ObjectBase::GetHeight()
{
	return _height;
}

void ObjectBase::SetVisible(bool value)
{
	_visible = value;
}

int  ObjectBase::GetID() const
{
	return _id;
}

void ObjectBase::SetID(int id)
{
	_id = id;
}
