#pragma once
#include "Components/Component.h"

class ComponentType;

using ComponentID = uint16_t;

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();
	void UpdateComponents();
	Component* CreateComponent(Component::ComponentType componentType);
	ComponentID getCounter() { return mLastComponentID; };
private:
	ComponentID mLastComponentID;
	ComponentType* mComponentType;
	std::vector<std::unique_ptr<Component>> mComponents;
};