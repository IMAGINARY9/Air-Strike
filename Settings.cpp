#include "Settings.h"

bool& Settings::isGameRunning()
{
	static bool iGR = false;
	return iGR;
}

int& Settings::Volume()
{
	static int vl = 50;
	return vl;
}

float& Settings::Difficult()
{
	static float df = 1;
	return df;
}

void Settings::SetIsGameRunning(bool value)
{
	isGameRunning() = value;
}
bool Settings::GetIsGameRunning() {
	return isGameRunning();
}

void Settings::SetVolume(int value)
{
	Volume() = value;
}
int Settings::GetVolume()
{
	return Volume();
}

void Settings::SetDifficult(float value)
{
	Difficult() = value;
}

float Settings::GetDifficult()
{
	return Difficult();
}
