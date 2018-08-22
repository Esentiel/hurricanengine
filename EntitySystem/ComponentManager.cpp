#include "stdafx.h"
#include "ComponentManager.h"

ComponentManager::ComponentManager() : mLastComponentID(1)
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
	//switching components as example - shoule be rewrited
	switch (componentType)
	{
	case Component::ComponentType::TestComponent:
	{	
		//creating new component 
		std::unique_ptr<Component> ComponentPointer = std::make_unique<TestComponent>(mLastComponentID);
		if (ComponentPointer)
		{
			ptr = ComponentPointer.get();
			mComponents.push_back(std::move(ComponentPointer));
		}
		break;
	}
	default:
		return nullptr;
	}
	++mLastComponentID;
	return ptr;
}
