#pragma once
#include <SFML/System/Clock.hpp>
using namespace sf;
class Timer
{
private:
	Timer();
	static Clock& dtClock();
	static float& timeScale();
	static float& delta();
public:
	static float GetTimeScale();
	static void SetTimeScale(float);
	static float deltaTime();
	static void tickUpdate();
};