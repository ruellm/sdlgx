// This class should handle all the callback on the app.
// instead of callback function, reciever should inherit from this class
// Event type should be define per application
// Created Nov 1, 2016
#pragma once

class ICustomEvent
{
public:
	// object is the actual object that trigger
	// int is the the event type defined per application
	virtual void OnCustomEvent(void* obj, int type) = 0;

};