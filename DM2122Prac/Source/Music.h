#pragma once
#define WITH_WINMM

#pragma comment (lib, "winmm.lib")
//#include "../../soloud20181119/include/soloud.h"
//#include "../../soloud20181119/include/soloud_wav.h"

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
using namespace std;

class Music
{
public:
	Music();
	~Music();
	void playBGM(int i);
	void playInstantSound(int i);
	void stopMusic();
private:
	//SoLoud::Soloud gSoloud;
	//SoLoud::Wav gWave;
};