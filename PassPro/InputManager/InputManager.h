#pragma once
#include <unordered_map>
#include <vector>
#include "../Delegate.h"

void OnKeyPressedFunction();

class InputManager
{
public:
	/* Getter for singleton instance */
	static InputManager* Get();

	/*** Key Pressed Functions ***/

	void HandleKeyPressed(unsigned int KeyCode);

	void BindToKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

	template<typename CallbackObjectType>
	void BindToKeyPressed(unsigned int KeyCode, CallbackObjectType* Object, void (CallbackObjectType::* Function)()) { BindToKeyPressed(KeyCode, new DelegateCallback<CallbackObjectType>(Object, Function)); };
	
	void UnbindFromKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

	/* Unbind all functions bound to the given key code on the given object*/
	template<typename CallbackObjectType>
	void UnbindAllFromKeyPressed(unsigned int KeyCode, CallbackObjectType* Object)
	{
		auto KeyDelegatePair = KeyPressedDelegateMap.find(KeyCode);
		if (KeyDelegatePair != KeyPressedDelegateMap.end())
		{
			KeyDelegatePair->second.Unbind(Object);
		}
	}

	/*** Key Released Functions ***/

	void HandleKeyReleased(unsigned int KeyCode);

	void BindToKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback);

	template<typename CallbackObjectType>
	void BindToKeyReleased(unsigned int KeyCode, CallbackObjectType* Object, void (CallbackObjectType::* Function)()) { BindToKeyReleased(KeyCode, new DelegateCallback<CallbackObjectType>(Object, Function)); };

	void UnbindFromKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback);

	/* Unbind all functions bound to the given key code on the given object*/
	template<typename CallbackObjectType>
	void UnbindAllFromKeyReleased(unsigned int KeyCode, CallbackObjectType* Object)
	{
		auto KeyDelegatePair = KeyReleasedDelegateMap.find(KeyCode);
		if (KeyDelegatePair != KeyReleasedDelegateMap.end())
		{
			KeyDelegatePair->second.Unbind(Object);
		}
	}

private:
	InputManager() {}

	/* Singleton instance of this class */
	static InputManager* Instance;

	/* Map of KeyCodes that are being listened for with vector of functions to called when the key is pressed */
	std::unordered_map<unsigned int, Delegate> KeyPressedDelegateMap;

	/* Map of KeyCodes that are being listened for with vector of functions to called when the key is released */
	std::unordered_map<unsigned int, Delegate> KeyReleasedDelegateMap;
};