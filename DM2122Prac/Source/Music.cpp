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
	}
}

void  Music::playInstantSound(int i)
{
	switch (i)
	{
	case 0:
		break;
	}
}

void Music::stopMusic()
{
	PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
}