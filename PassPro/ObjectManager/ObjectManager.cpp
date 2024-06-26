#include "ObjectManager.h"
using namespace std;

ObjectManager::~ObjectManager()
{
	for (auto& Object : Objects)
		delete Object.second;

	Objects.clear();
}

Object* ObjectManager::FindObjectByName(const char* name)
{
	if (Objects.count(name) > 0)
		return Objects[name];
	else
		return nullptr;
}

void ObjectManager::AddObject(Object* Object)
{
	AddObject(Object, Object->Name.c_str());
}

void ObjectManager::AddObject(Object* NewObject, const char* InName)
{
	NewObject->ObjectManager = this;
	string Name = InName;

	// If the amount of objects with the same name is greater than 0
	if (Objects.count(Name) > 0)
	{
		string NewName;
		unsigned int ObjectNum = 0;
		string OrigName = Name;

		// Continue increasing a number at the end of the original name until a unique one is found
		while (Objects.count(Name) > 0)
		{
			NewName = OrigName + std::to_string(ObjectNum);
			Name = NewName.c_str();
			ObjectNum++;
		}
	}

	NewObject->Name = Name;
	Objects.insert(pair<string, Object*>(Name, NewObject));
	PriorityObjects.push_back(NewObject);
	sort(PriorityObjects.begin(), PriorityObjects.end(), [&](Object* lhs, Object* rhs) {return lhs->Priority > rhs->Priority; });
}

void ObjectManager::DestroyObject(const char* name)
{
	for (size_t i = 0; i < PriorityObjects.size(); i++)
	{
		if (PriorityObjects[i] == Objects[name]) {
			PriorityObjects.erase(PriorityObjects.begin() + i);
			break;
		}
	}
	delete Objects[name];
	Objects.erase(name);
}

void ObjectManager::DestroyObject(Object* Object)
{
	for (auto& object : Objects)
	{
		if (object.second == Object)
		{
			delete object.second;
			Objects.erase(object.first);
			break;
		}
	}

	for (size_t i = 0; i < PriorityObjects.size(); i++)
	{
		if (PriorityObjects[i] == Object) 
		{
			PriorityObjects.erase(PriorityObjects.begin() + i);
			break;
		}
	}
}

void ObjectManager::Update(double deltaTime)
{
	for (int o = 0; o < PriorityObjects.size(); o++)
	{
		if (PriorityObjects[o]->IsActive())
		{
			PriorityObjects[o]->Update(deltaTime);
		}
	}
}

void ObjectManager::Render()
{
	for (int o = 0; o < PriorityObjects.size(); o++)
	{
		if (PriorityObjects[o]->IsActive())
		{
			PriorityObjects[o]->Render();
		}
	}
}
