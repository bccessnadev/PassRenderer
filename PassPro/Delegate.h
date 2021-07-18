#pragma once

#include<vector>

class IDelegateCallback
{
public:
	virtual void operator()() = 0;
	virtual bool operator==(IDelegateCallback* Other) = 0;
};

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
	CallbackObjectType* CallbackObject;

	void (CallbackObjectType::*FunctionToCall)();	
};

class Delegate
{
public:
	 
	void Bind(IDelegateCallback* Callback);

	template<typename CallbackObjectType>
	void Bind(CallbackObjectType* CallBackObject, void (CallbackObjectType::*FunctionToCall)()) { Bind(new DelegateCallback<CallbackObjectType>(CallBackObject, FunctionToCall)); }

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

	void Broadcast();

private:
	std::vector<IDelegateCallback*> CallbackArray;

};
