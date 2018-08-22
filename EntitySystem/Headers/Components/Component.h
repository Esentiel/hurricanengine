#pragma once
#include "stdafx.h"

class Entity;

using ComponentID = uint16_t;

class Component
{
public:
	enum class ComponentType
	{
		eRenderingComponent = 0,
		eNetworkComponent,
		TestComponent
	};
	Component(ComponentID id) : mUniqueID(id) {};
	virtual void UpdateComponent() = 0;
	ComponentID GetComponentID() const;
	virtual ~Component() {};
private:
	// it's unnecessary in this abstract class
	ComponentID mUniqueID;
	//Component has a pointer to his owner
	Entity* mEntity;
	ComponentType mComponentType;
};