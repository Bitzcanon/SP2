#include "Music.h"

Music::Music()
{
	//gSoloud.init();
}

Music::~Music()
{
	//gSoloud.deinit();
}

void Music::playBGM(int i)
{
	switch (i)
	{
	case 0:
		PlaySound(TEXT("Sounds//Silhouette.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 1:
		PlaySound(TEXT("Sounds//Snow Halation.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
}

void  Music::playInstantSound(int i)
{
	switch (i)
	{
	case 0:
		PlaySound(TEXT("Sounds//Boost.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 1:
		PlaySound(TEXT("Sounds//CollectCoin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 2:
		PlaySound(TEXT("Sounds//Crash.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 3:
		PlaySound(TEXT("Sounds//Damage.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 4:
		PlaySound(TEXT("Sounds//LoseSound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 5:
		PlaySound(TEXT("Sounds//Reverse.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 6:
		PlaySound(TEXT("Sounds//Slowdown.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	case 7:
		PlaySound(TEXT("Sounds//Winsound.wav"), NULL, SND_FILENAME | SND_ASYNC);
		break;
	}
}

void Music::stopMusic()
{
	PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
}