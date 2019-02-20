#pragma once
#define WITH_WINMM

#include "../../soloud20181119/include/soloud.h"
#include "../../soloud20181119/include/soloud_wav.h"

using namespace std;

class Music
{
public:
	Music();
	~Music();
	void playBGM(int i);
	void playInstantSound(int i);
private:
	SoLoud::Soloud gSoloud;
	SoLoud::Wav gWave;
};