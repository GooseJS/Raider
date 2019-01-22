#pragma once

#include <map>
#include <list>
#include <functional>
#include <typeindex>

#include "Raider/Logger.h"
#include "Raider/event/IEvent.h"

#define RD_SUBSCRIBE_EVENT(EventHandler) std::bind(EventHandler, this, std::placeholders::_1)

namespace Raider
{
	class EventSystemSubscription
	{
	private:
		struct AbstractHandler
		{
			virtual ~AbstractHandler() {}
			virtual void handle(IEvent& event) = 0;
		};

		template <typename EventType, typename EventHandler>
		struct Handler : AbstractHandler
		{
			EventHandler eventHandler;
			explicit Handler(EventHandler handler) : eventHandler(std::move(handler)) {}
			void handle(IEvent& event) final { eventHandler(static_cast<EventType&>(event)); }
		};

		std::shared_ptr<AbstractHandler> _handler;
	public:
		template <typename EventType, typename EventHandler>
		EventSystemSubscription(EventType*, EventHandler& handler) : _handler(std::make_shared<Handler<EventType, EventHandler>>(handler)) {}
		template <typename EventType>
		void handleEvent(EventType event)
		{
			_handler->handle(static_cast<EventType&>(event));
		}

	};

	class EventSystem
	{
	public:
		typedef std::function<void(IEvent&)> EventFunctionOld;
		typedef std::multimap<const std::type_index, EventSystemSubscription> EventMap;

	private:
		EventMap _eventDB;

		EventSystem() = default;
		~EventSystem() = default;
		EventSystem(const EventSystem& es) = delete;
		EventSystem& operator=(const EventSystem& es) = delete;

	public:
		RD_STATIC_GET_INSTANCE(EventSystem)

		template <typename EventType, typename EventFunction>
		void addListener(EventFunction listenerFunction)
		{
			RD_CORE_TRACE("Adding event listener.");
			EventType* event{};
			EventSystemSubscription subscription { event, listenerFunction };
			auto typeIndex = std::type_index(typeid(EventType));
			auto pair = std::make_pair(typeIndex, subscription);
			_eventDB.insert(pair);
		}

		template <typename EventType>
		void dispatchEvent(EventType& event)
		{
			auto range = _eventDB.equal_range(std::type_index(typeid(EventType)));

			IEvent& handledEvent = static_cast<IEvent&>(event);

			for (auto iter = range.first; iter != range.second; iter++)
			{
				if (handledEvent.handled())
					break;
				auto eventSubscription = iter->second;
				eventSubscription.handleEvent(event);
			}
		}
	};
}