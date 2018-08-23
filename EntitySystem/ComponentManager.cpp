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
		//creating new component 
		std::unique_ptr<Component> ComponentPointer = std::make_unique<eNetworkComponent>(mNextComponentID);
		if (ComponentPointer)
		{
			ptr = ComponentPointer.get();
			mComponents.push_back(std::move(ComponentPointer));
		}
		break;
	}
	case Component::ComponentType::eRenderingComponent:
	{
		//creating new component 
		std::unique_ptr<Component> ComponentPointer = std::make_unique<eRenderingComponent>(mNextComponentID);
		if (ComponentPointer)
		{
			ptr = ComponentPointer.get();
			mComponents.push_back(std::move(ComponentPointer));
		}
		break;
	}
	}
	++mNextComponentID;
	return ptr;
}

const Component* ComponentManager::GetComponentById(Component::ComponentType componentType, ComponentID componentID)
{
	Component* ComponentPtr = nullptr;
	
	switch (componentType)
	{
	case Component::ComponentType::eNetworkComponent:
	{
		for (std::unique_ptr<Component> &component : mComponents) 
		{
			if (component->GetComponentID() == componentID)
			{
				ComponentPtr = component.get();
			}
		}
		break;
	}
	}
	return ComponentPtr;
	
}
