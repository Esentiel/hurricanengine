#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::AddComponent(Component* component)
{
	mComponents.push_back(component);
}

bool Entity::IsActive() const
{
	return mIsActive;
}

void Entity::Activate(bool flag)
{
	mIsActive = flag;
}

Component* Entity::GetComponent(Component::ComponentType componentType)
{
	return nullptr;
}
