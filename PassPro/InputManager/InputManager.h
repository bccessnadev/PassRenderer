#pragma once
#include <unordered_map>
#include <vector>
#include "../Delegate.h"

void OnKeyPressedFunction();

class InputManager
{
public:
	/** Getter for singleton instance */
	static InputManager* Get();

	/*** Key Pressed Functions ***/

	/**
	 * Broadcasts to any functions waiting for given key to be pressed.
	 * 
	 * \param Virtual-Key Code for the key that has been pressed
	 */
	void HandleKeyPressed(unsigned int KeyCode);

	/**
	 * Binds a callback to be called when the given key is pressed.
	 * 
	 * \param KeyCode Virtual-Key Code for the key that has been pressed
	 * \param Callback Callback to be called when key is pressed
	 */
	void BindToKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

	/**
	 * Creates a callback to be called when the given key is pressed.
	 * 
	 * \param KeyCode Virtual-Key Code for the key that has been pressed
	 * \param Object Object that function should be called on
	 * \param Function Function that should be called when key is pressed
	 */
	template<typename CallbackObjectType>
	void BindToKeyPressed(unsigned int KeyCode, CallbackObjectType* Object, void (CallbackObjectType::* Function)()) { BindToKeyPressed(KeyCode, new DelegateCallback<CallbackObjectType>(Object, Function)); };
	
	/**
	 * Unbind all functions bound to the given key on the given object.
	 *
	 * \param KeyCode Virtual-Key Code for the key that has been pressed
	 * \param Object Object that should no longer have callbacks for this key event triggered on
	 */
	void UnbindFromKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

	/**
	 * Unbind all functions bound to the given key on the given object.
	 * 
	 * \param KeyCode Virtual-Key Code for the key that has been pressed
	 * \param Object Object that should no longer have callbacks for this key event triggered on
	 */
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

	/**
	 * Broadcasts to any functions waiting for given key to be released.
	 *
	 * \param Virtual-Key Code for the key that has been released
	 */
	void HandleKeyReleased(unsigned int KeyCode);

	/**
	 * Binds a callback to be called when the given key is released.
	 *
	 * \param KeyCode Virtual-Key Code for the key that has been released
	 * \param Callback Callback to be called when key is released
	 */
	void BindToKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback);

	/**
	 * Creates a callback to be called when the given key is released.
	 *
	 * \param KeyCode Virtual-Key Code for the key that has been released
	 * \param Object Object that function should be called on
	 * \param Function Function that should be called when key is released
	 */
	template<typename CallbackObjectType>
	void BindToKeyReleased(unsigned int KeyCode, CallbackObjectType* Object, void (CallbackObjectType::* Function)()) { BindToKeyReleased(KeyCode, new DelegateCallback<CallbackObjectType>(Object, Function)); };

	/**
	 * Unbind all functions bound to the given key on the given object.
	 *
	 * \param KeyCode Virtual-Key Code for the key that has been released
	 * \param Object Object that should no longer have callbacks for this key event triggered on
	 */
	void UnbindFromKeyReleased(unsigned int KeyCode, IDelegateCallback* Callback);

	/**
	 * Unbind all functions bound to the given key on the given object.
	 *
	 * \param KeyCode Virtual-Key Code for the key that has been released
	 * \param Object Object that should no longer have callbacks for this key event triggered on
	 */
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

	/** Singleton instance of this class */
	static InputManager* Instance;

	/** Map of KeyCodes that are being listened for with vector of functions to called when the key is pressed */
	std::unordered_map<unsigned int, Delegate> KeyPressedDelegateMap;

	/** Map of KeyCodes that are being listened for with vector of functions to called when the key is released */
	std::unordered_map<unsigned int, Delegate> KeyReleasedDelegateMap;
};