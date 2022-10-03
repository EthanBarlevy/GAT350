#include "eventManager.h"

namespace vl
{
	void EventManager::Initialize()
	{
		//
	}

	void EventManager::Shutdown()
	{
		//
	}

	void EventManager::Update()
	{
		//
	}

	void EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObject* reciever)
	{
		Observer observer;
		observer.reciever = reciever;
		observer.function = function;

		m_events[name].push_back(observer);
	}

	void EventManager::Unsubscribe(const std::string& name, GameObject* reciever)
	{
		auto& observers = m_events[name];

		for (auto iter = observers.begin(); iter != observers.end(); iter++)
		{
			if (iter->reciever == reciever)
			{
				observers.erase(iter);
				break;
			}
		}
	}

	void EventManager::Notify(const Event& event)
	{
		auto& observers = m_events[event.name];
		for (auto& observer : observers)
		{
			if (!event.reciever || event.reciever == observer.reciever)
			{
				observer.function(event);
			}
		}
	}
}
