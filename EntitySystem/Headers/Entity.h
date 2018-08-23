#pragma once
#include "Components/Component.h"

class Entity
{
public:
	Entity();
	~Entity();
	void AddComponent(Component::ComponentType CompType, Component* component);
	bool IsActive() const;
	void Activate(bool flag);
	const Component* GetComponent(Component::ComponentType componentType);
private: 
	bool mIsActive = true;
	std::unordered_map<Component::ComponentType, Component*> mComponents;
};

