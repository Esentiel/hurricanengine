#pragma once
#include "Components/Component.h"


class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();
	void UpdateComponents();
	Component* CreateComponent(Component::ComponentType componentType);
	const ComponentID GetLastComponentID() { return mNextComponentID; };
	const Component* GetComponentById(Component::ComponentType componentType, ComponentID componentID);
private:
	ComponentID mNextComponentID;
	//In the future there will be one separate vector for each component in according to ComponentType
	std::vector<std::unique_ptr<Component>> mComponents;
};