#include "Object.h"
#include <queue>

using namespace std;

int Object::CurrentInstanceID = 0;

Object::Object()
{
	InstanceID = CurrentInstanceID++;
}

Object::Object(const std::string ObjectName)
{
	InstanceID = CurrentInstanceID++;
	Name = ObjectName;
}

Object::~Object()
{
	for (int c = 0; c < Components.size(); c++)
		delete Components[c];

	Components.clear();
}

void Object::AddComponent(IComponent* Component)
{
	if (Component)
	{
		Components.push_back(Component);
		sort(Components.begin(), Components.end(), [&](IComponent* Lhs, IComponent* Rhs) {return Lhs->Priority < Rhs->Priority; });
	}
}

std::vector<IComponent*> Object::GetAllComponents()
{
	return Components;
}

void Object::Update(double DeltaTime)
{
	if (bIsActive)
	{
		for (int c = 0; c < Components.size(); c++)
			Components[c]->Update(DeltaTime);
	}
}

void Object::Render()
{
	if (bIsActive)
	{
		for (int c = 0; c < Components.size(); c++)
			Components[c]->Render();
	}
}

void Object::RemoveComponent(IComponent* ComponentToRemove)
{
	if (ComponentToRemove)
	{
		for (size_t i = 0; i < Components.size(); i++)
		{
			if (Components[i] == ComponentToRemove)
			{
				Components.erase(Components.begin() + i);
				delete ComponentToRemove;
			}
		}
	}
}
