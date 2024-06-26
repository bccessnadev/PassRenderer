#pragma once

#include<vector>

/** Interface for function that can be called back */
class IDelegateCallback
{
public:
	virtual void operator()() = 0;
	virtual bool operator==(IDelegateCallback* Other) = 0;
};

/**
 * Method of storing a function pointer to be called when a delegate is broadcasted.
 * CallbackObjectType is the class of the object that has the function to be called
 */
template<typename CallbackObjectType>
class DelegateCallback : public IDelegateCallback
{
public:
	DelegateCallback(CallbackObjectType* Object, void (CallbackObjectType::*Function)()) : CallbackObject(Object), FunctionToCall(Function) {}

	virtual void operator()() override { (CallbackObject->*FunctionToCall)(); }
	virtual bool operator==(IDelegateCallback* Other) override
	{
		if (DelegateCallback* OtherDelegateCallBack = dynamic_cast<DelegateCallback*>(Other))
		{
			return FunctionToCall == OtherDelegateCallBack->FunctionToCall &&
				CallbackObject == OtherDelegateCallBack->CallbackObject;
		}

		return false;
	}

	virtual bool operator==(CallbackObjectType* Other) { return CallbackObject == Other; }

private:
	/** Object that the function should be called on */
	CallbackObjectType* CallbackObject;

	/** Pointer to function to call on broadcast */
	void (CallbackObjectType::*FunctionToCall)();	
};

/** Represents an event that can be listened to and broadcasted */
class Delegate
{
public:
	 /** Bind a callback function to be called when the delegate is broadcasted */
	void Bind(IDelegateCallback* Callback);

	/** Create a callback to be called when the delegate is broadcasted */
	template<typename CallbackObjectType>
	void Bind(CallbackObjectType* CallBackObject, void (CallbackObjectType::*FunctionToCall)()) { Bind(new DelegateCallback<CallbackObjectType>(CallBackObject, FunctionToCall)); }

	/** Remove a callback from this delegate */
	void Unbind(IDelegateCallback* Callback);

	/* Unbind all callbacks on a given object */
	template<typename CallbackObjectType>
	void Unbind(CallbackObjectType* Object)
	{
		for (auto Callback : CallbackArray)
		{
			if (DelegateCallback<CallbackObjectType>* DCallback = dynamic_cast<DelegateCallback<CallbackObjectType>*>(Callback))
			{
				if (*DCallback == Object)
				{
					Unbind(Callback);
				}
			}
		}
	}

	/** Calls all of the bound callback functions */
	void Broadcast();

private:
	/** Container of callback functions to call when Broadcast occurs */
	std::vector<IDelegateCallback*> CallbackArray;

};
