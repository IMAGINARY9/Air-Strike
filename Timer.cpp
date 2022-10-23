#include "Timer.h"

Timer::Timer() {}
Clock& Timer::dtClock() {
	static Clock dtc;
	return dtc;
}
float& Timer::timeScale() {
	static float ts = 1;
	return ts;
}
float& Timer::delta() {
	static float d = 0;
	return d;
}
float Timer::GetTimeScale() {
	return timeScale();
}
void Timer::SetTimeScale(float value) {
	timeScale() = value;
}
float Timer::deltaTime() {
	return delta() * timeScale();
}
void Timer::tickUpdate() {
	delta() = dtClock().restart().asSeconds();
}