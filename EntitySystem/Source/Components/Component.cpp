#include "stdafx.h"
#include "Components/Component.h"

Component::Component(ComponentID id) : mUniqueID(id)
{
}

Component::~Component()
{
}

ComponentID Component::GetComponentID() const
{
	return mUniqueID;
}