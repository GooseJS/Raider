#pragma once

#include <vector>
#include <chrono>

#define RD_GET_CURRENT_TIME_MILLIS std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()

namespace Raider
{
	class Application;
	class RaiderTime
	{
	private:
		double _lastFrameTime;
		double _currentFrameTime;
		float _deltaTime;
		friend Application;
	public:
		double getLastFrameTime() const { return _lastFrameTime; }
		double getCurrentFrameTime() const { return _currentFrameTime; }
		float getDeltaTime() const { return _deltaTime; }
		double getCurrentTimeInMS() const { return RD_GET_CURRENT_TIME_MILLIS; }
	};

	class RaiderDebugTimer
	{
	public:
		struct RaiderDebugSection
		{
			RaiderDebugSection(const char* _name) : name(_name) {}

			const char* name;

			int timesRun = 0;

			double lastTime = 0;

			double avgTimeTaken = 0;
			double lastTimeTaken = 0;
			double totalTimeTaken = 0;

			float percentageTaken = 0; // TODO: Decide if I'm going to use this
		};
	private:
		RaiderDebugSection* _currentSection = nullptr;

		std::vector<RaiderDebugSection> _sections;
		const char* _name = "";

	public:
		RaiderDebugTimer(const char* name) : _name(name) {}
		
		void startSection(const char* sectionName)
		{
			if (_currentSection != nullptr && _currentSection->name == sectionName)
			{
				_currentSection->lastTime = RD_GET_CURRENT_TIME_MILLIS;
				return;
			}

			for (auto& section : _sections)
			{
				if (section.name == sectionName)
				{
					_currentSection = &section;
					_currentSection->lastTime = RD_GET_CURRENT_TIME_MILLIS;
					return;
				}
			}

			_sections.emplace_back(sectionName);
			_currentSection = &_sections.back();
			_currentSection->lastTime = RD_GET_CURRENT_TIME_MILLIS;
		}

		RaiderDebugSection endSection()
		{
			_currentSection->lastTimeTaken = RD_GET_CURRENT_TIME_MILLIS - _currentSection->lastTime;
			_currentSection->totalTimeTaken += _currentSection->lastTimeTaken;
			_currentSection->timesRun++;
			_currentSection->avgTimeTaken = _currentSection->totalTimeTaken / static_cast<double>(_currentSection->timesRun);
			RaiderDebugSection result = *_currentSection;
			return result;
		}

		RaiderDebugSection startEndSection(const char* name)
		{
			RaiderDebugSection result = endSection();
			startSection(name);
			return result;
		}

	};
}