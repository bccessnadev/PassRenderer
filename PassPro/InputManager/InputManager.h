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

	void HandleKeyPressed(unsigned int KeyCode);

	void BindToKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

	void UnbindFromKeyPressed(unsigned int KeyCode, IDelegateCallback* Callback);

private:
	InputManager() {}

	/* Singleton instance of this class */
	static InputManager* Instance;

	// Function to call and pointer to object to call it on
	typedef std::pair<void*, void (*)()> ObjectFunctionPair;

	// Map of KeyCodes that are being listened for with vector of functions to called when the key is pressed
	std::unordered_map<unsigned int, Delegate> KeyPressedDelegateMap;
};