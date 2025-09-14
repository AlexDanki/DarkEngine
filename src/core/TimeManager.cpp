#include "TimeManager.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono;

TimeManager::TimeManager(double targetFPS)
    : m_targetFrameTime(1.0 / targetFPS),
    m_deltaTime(0.0),
    m_frameStart(),
    m_frameEnd()
{
}

void TimeManager::startTime()
{
    m_frameStart = high_resolution_clock::now();
}

void TimeManager::endTime()
{
    m_frameEnd = high_resolution_clock::now();
    m_deltaTime = duration<double>(m_frameEnd - m_frameStart).count();
}

void TimeManager::sleepIfNeeded()
{
    // Clamp deltaTime to avoid large frame jumps
    m_deltaTime = std::min(m_deltaTime, 0.05);

    double sleepTime = std::max(0.0, m_targetFrameTime - m_deltaTime);
    if (sleepTime > 0.0)
    {
        std::this_thread::sleep_for(duration<double>(sleepTime));

        // Recalculate deltaTime after sleeping
        m_frameEnd = high_resolution_clock::now();
        m_deltaTime = duration<double>(m_frameEnd - m_frameStart).count();
    }
}

