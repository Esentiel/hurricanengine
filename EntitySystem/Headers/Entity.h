#pragma once
#include "Components/Component.h"


class Entity
{
public:
	Entity();
	~Entity();
	void AddComponent(Component* component);
	bool IsActive() const;
	void Activate(bool flag);
	Component* GetComponent(Component::ComponentType componentType);
private: 
	//if the Entity is not active it should be deleted
	bool mIsActive = true;
	//list of Components the Entity is holding
	std::vector<Component*> mComponents;
};

