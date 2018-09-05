#include "stdafx.h"
#include "ComponentManager.h"


ComponentManager::ComponentManager() : mNextComponentID(1)
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::UpdateComponents()
{
	for (std::unique_ptr<Component> &component : mComponents)
	{
		component->UpdateComponent();
	}
}

Component* ComponentManager::CreateComponent(Component::ComponentType componentType)
{
	Component* ptr = nullptr;
	switch (componentType)
	{
	case Component::ComponentType::eNetworkComponent:
	{
		//creating unique_ptr to Component with appropriate ComponentType and push_back it to the vector
	}
	}
	if (ptr)
	{
		++mNextComponentID;
	}
	return ptr;
}

const Component* ComponentManager::GetComponentById(Component::ComponentType componentType, ComponentID componentID)
{
	Component* componentPtr = nullptr;
	
	switch (componentType)
	{
	case Component::ComponentType::eNetworkComponent:
	{
		for (std::unique_ptr<Component> &component : mComponents) 
		{
			if (component->GetComponentID() == componentID)
			{
				componentPtr = component.get();
			}
		}
		break;
	}
	}
	return componentPtr;
	
}
