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
	mComponents.insert(std::pair<Component::ComponentType, Component*>(ComponentType, component));
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
	Component* entityComponentPtr = nullptr;

	auto it = mComponents.find(componentType);

	if (it != mComponents.end())
	{
		entityComponentPtr = it->second;
	}

	return entityComponentPtr;
}
