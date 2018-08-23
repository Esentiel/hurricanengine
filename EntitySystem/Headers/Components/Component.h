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
		eNetworkComponent
	};
	Component(ComponentID id);
	virtual void UpdateComponent() = 0;
	ComponentID GetComponentID() const;
	virtual ~Component();
private:
	Entity* mEntity;
	ComponentID mUniqueID;
	ComponentType mComponentType;
};
