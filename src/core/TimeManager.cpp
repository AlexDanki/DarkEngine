#include "TimeManager.h"
#include  <iostream>

TimeManager::TimeManager(double targetFPS)
	:m_targetFrameTime(1.0 / targetFPS),
	m_deltaTime(0.0),
	m_frameStart(),
	m_frameEnd()
{
}

void TimeManager::startTime()
{
	m_frameStart = std::chrono::high_resolution_clock::now();
}

void TimeManager::endTime()
{
	m_frameEnd = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = m_frameEnd - m_frameStart;
	m_deltaTime = elapsed.count();
}

void TimeManager::sleepIfNeeded()
{
    if (m_deltaTime > 0.05f)
        m_deltaTime = 0.05f;

    double sleepTime = std::max(0.0, m_targetFrameTime - m_deltaTime);
    if (sleepTime > 0.0) {
        auto sleepStart = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));

        while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - sleepStart).count() < sleepTime) {}

        // Recalcular deltaTime após o sleep
        m_frameEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = m_frameEnd - m_frameStart;
        m_deltaTime = elapsed.count();
    }
}

