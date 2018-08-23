#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::AddComponent(Component::ComponentType ComponentType,Component* component)
{
	mComponents[ComponentType] = component;
}

bool Entity::IsActive() const
{
	return mIsActive;
}

void Entity::Activate(bool flag)
{
	mIsActive = flag;
}

const Component* Entity::GetComponent(Component::ComponentType componentType)
{
	Component* EntityComponentPtr = nullptr;
	
	for (std::pair<Component::ComponentType, Component*> component : mComponents)
	{
		if (component.first == componentType)
		{
			EntityComponentPtr = component.second;
		}
	}
	return EntityComponentPtr;
}
