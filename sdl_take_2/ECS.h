#pragma once
#include "Includes.h"

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID GetNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID GetComponentTypeID() noexcept
{
	static ComponentID typeID = GetNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

// used to compare component number to see if all components are present
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;

// array of all components set to the length of the max components
using ComponentArray = std::array<Component*, maxComponents>;








class Component
{
public:
	Entity* entity;

	virtual void Init(){}
	virtual void Update(){}
	virtual void Draw(){}

	virtual ~Component(){}
};













class Entity
{


private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager)
	{

	}
	void Update()
	{
		for (auto& c : components) c->Update();
		
	}

	void Draw() 
	{
		for (auto& c : components) c->Draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }


	bool hasGroup(Group mGroup)
	{
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGrourp);
	void delGroup(Group mGroup)
	{
		groupBitSet[mGroup] = false;
	}

	// check if entity has components as bool
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[GetComponentTypeID<T>()];
	}




	// add component to entity
	template <typename T, typename... TArgs> 
	T& AddComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		// every component type will always be put in the same position in the array
		componentArray[GetComponentTypeID<T>()] = c;
		componentBitSet[GetComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T> T& GetComponent() const
	{
		auto ptr(componentArray[GetComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	//example
	//gameobject.GetComponent<PositionComponent>().setXpos(25);
};













class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void Update()
	{
		for (auto& e : entities) e->Update();
	}

	void Draw()
	{
		for (auto& e : entities) e->Draw();
	}

	void Refresh()
	{
		for (auto i = 0u; i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity)
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}


		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),

			//removes inactive entities
			std::end(entities));
	}


	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}


	//adds entity 
	Entity& AddEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };

		//adds entity ptr to entity vector list
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};
