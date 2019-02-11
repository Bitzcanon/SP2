#include "music.h"

vector<MLoaded> LoadedFiles;

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void Mshutdown()
{
	mciSendCommand(MCI_ALL_DEVICE_ID, MCI_CLOSE, MCI_WAIT, NULL);
}

void MusicInit()
{
	MLoaded loaded;

	MusicLoad("gamemusic.mp3", "mpegvideo", "gamemusic", "75", &loaded);
	LoadedFiles.push_back(loaded);
	LoadedFiles.push_back(loaded);
}
bool MusicLoad(string file, string type, string alias, string initialvolume, MLoaded* Returnfile)
{
	MCIERROR me;
	string buff;
	buff = "open \"" + file + "\" type " + type + " alias " + alias;
	me = mciSendString(s2ws(buff).c_str(), NULL, 0, NULL);
	if (me == 0)
	{
		(*Returnfile).status = 0;
		(*Returnfile).file = file;
		(*Returnfile).type = type;
		(*Returnfile).alias = alias;
		buff = "setaudio " + alias + " volume to " + initialvolume;
		me = mciSendString(s2ws(buff).c_str(), NULL, 0, NULL);
		return true;
	}
	else
	{
		(*Returnfile).status = me;
		return false;
	}

}
bool MusicPlay(string alias, string arguments)
{
	MCIERROR ME;
	string constructstring = "play ";
	constructstring += alias;
	constructstring += " " + arguments;
	ME = mciSendString(s2ws(constructstring).c_str(), NULL, 0, NULL);
	if (ME != 0)
		return false;
	else
		return true;
}
bool MusicStop(string alias)
{
	MCIERROR ME;
	string constructstring = "stop ";
	constructstring += alias;
	ME = mciSendString(s2ws(constructstring).c_str(), NULL, 0, NULL);
	if (ME != 0)
		return false;
	else
		return true;
}
