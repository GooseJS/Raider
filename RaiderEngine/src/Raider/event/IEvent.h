#pragma once

namespace Raider
{
	struct IEvent
	{
	private:
		bool _handled = false;
	public:
		void handle(bool handle) { _handled = handle; }
		bool handled() const { return _handled; }
		IEvent() = default;
		virtual ~IEvent() = default;
	};

	struct IEventCancellable : public IEvent
	{
	private:
		bool _cancelled = false;
	public:
		void cancel(bool cancelled) { _cancelled = cancelled; }
		bool cancelled() const { return _cancelled; }
		IEventCancellable() {}
		virtual ~IEventCancellable() = default;
	};
}