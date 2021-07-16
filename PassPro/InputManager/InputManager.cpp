#include "InputManager.h"

using namespace std;

InputManager* InputManager::Instance = nullptr;

InputManager* InputManager::Get()
{
	if (!Instance)
	{
		Instance = new InputManager();
	}

	return Instance;
}

void InputManager::HandleKeyPressed(unsigned int KeyCode)
{
	auto KeyDelegatePair = KeyPressedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyPressedDelegateMap.end())
	{
		KeyDelegatePair->second.Broadcast();
	}
}

void InputManager::BindToKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback)
{
	auto KeyDelegatePair = KeyPressedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyPressedDelegateMap.end())
	{
		KeyDelegatePair->second.Bind(Callback);
	}
	else
	{
		Delegate NewDelegate;
		NewDelegate.Bind(Callback);
		KeyPressedDelegateMap.emplace(KeyCode, NewDelegate);
	}
}

void InputManager::UnbindFromKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback)
{
	auto KeyDelegatePair = KeyPressedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyPressedDelegateMap.end())
	{
		KeyDelegatePair->second.Unbind(Callback);
	}
}

void InputManager::HandleKeyReleased(unsigned int KeyCode)
{
	auto KeyDelegatePair = KeyReleasedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyReleasedDelegateMap.end())
	{
		KeyDelegatePair->second.Broadcast();
	}
}

void InputManager::BindToKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback)
{
	auto KeyDelegatePair = KeyReleasedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyReleasedDelegateMap.end())
	{
		KeyDelegatePair->second.Bind(Callback);
	}
	else
	{
		Delegate NewDelegate;
		NewDelegate.Bind(Callback);
		KeyReleasedDelegateMap.emplace(KeyCode, NewDelegate);
	}
}

void InputManager::UnbindFromKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback)
{
	auto KeyDelegatePair = KeyReleasedDelegateMap.find(KeyCode);
	if (KeyDelegatePair != KeyReleasedDelegateMap.end())
	{
		KeyDelegatePair->second.Unbind(Callback);
	}
}
