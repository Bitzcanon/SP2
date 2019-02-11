#pragma once
#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;
std::wstring s2ws(const std::string& s);
void Mshutdown();
void MusicInit();
struct MLoaded
{
	std::string file = ""; // Can be empty!
	std::string type = ""; // Can be empty!
	std::string alias = ""; // Can be empty!
	int status;
};
bool MusicLoad(std::string file, std::string type, std::string alias, std::string initalvolume, MLoaded* Returnfile);
bool MusicPlay(string alias, string arguments);
bool MusicStop(string alias);



#endif
