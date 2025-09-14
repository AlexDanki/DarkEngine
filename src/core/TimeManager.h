#pragma once
#include <chrono>
#include <thread>

class TimeManager {
public:
	TimeManager(double targetFPS);

	void startTime();
	void endTime();
	void sleepIfNeeded();
	double getDeltaTime() const { return m_deltaTime; }

private:
	double m_targetFrameTime;
	double m_deltaTime;

	std::chrono::high_resolution_clock::time_point m_frameStart;
	std::chrono::high_resolution_clock::time_point m_frameEnd;
};
