#pragma once
const int W = 1920;
const int H = 1080;
class Settings
{
private:
	static bool& isGameRunning();
	static int& Volume();
	static float& Difficult();
public:
	static void SetIsGameRunning(bool);
	static bool GetIsGameRunning();
	static void SetVolume(int);
	static int GetVolume();
	static void SetDifficult(float);
	static float GetDifficult();
};

