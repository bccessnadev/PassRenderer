#include "Delegate.h"

using namespace std;

void Delegate::Bind(IDelegateCallback* Callback)
{
	// Try to find an instance of this exact callback in the callback array. If one is found, return to avoid duplicates
	vector<IDelegateCallback*>::iterator FoundInstance = find(CallbackArray.begin(), CallbackArray.end(), Callback);
	if (FoundInstance != CallbackArray.end())
	{
		return;
	}

	CallbackArray.push_back(Callback);
}

void Delegate::Unbind(IDelegateCallback* Callback)
{
	vector<IDelegateCallback*>::iterator FoundInstance = find(CallbackArray.begin(), CallbackArray.end(), Callback);
	if (FoundInstance != CallbackArray.end())
	{
		delete *FoundInstance;
		CallbackArray.erase(FoundInstance);
	}
}

void Delegate::Broadcast()
{
	for (IDelegateCallback* Callback : CallbackArray)
	{
		(*Callback)();
	}
}
