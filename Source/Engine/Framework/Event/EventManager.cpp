#include "EventManager.h"
#include "Core/Logger.h"

void kiko::EventManager::Update(float dt)
{

}

void kiko::EventManager::Subscribe(Event::id_t id, IEventListener* listener, eventFunction function)
{
	EventDispatcher dispatcher;

	dispatcher.listener = listener;
	dispatcher.function = function;

	INFO_LOG("Event subscribed: " + id);

	m_dispatchers[id].push_back(dispatcher);
}

void kiko::EventManager::Unsubscribe(Event::id_t id, IEventListener* listener)
{

}

void kiko::EventManager::DispatchEvent(Event::id_t id, Event::data_t data)
{
	Event event{ id, data };

	if (m_dispatchers.find(id) != m_dispatchers.end())
	{
		auto& dispatchers = m_dispatchers[id];
		for (auto& dispatcher : dispatchers)
		{
			dispatcher.function(event);
		}
	}
}
