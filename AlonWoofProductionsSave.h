#pragma once
#ifndef _ALONWOOFPRODUCTIONSSAVE_H_
#define _ALONWOOFPRODUCTIONSSAVE_H_

#define ALONWOOFMAGIC 0x52504C41
#define MOD_MAJOR_VERSION 0
#define MOD_MINOR_VERSION 7

#include <Windows.h>
#include <string>

using namespace std;

// A way to keep track of my mods.
// It's a surprise tool to help us later.

void saveNudeModData();
void writeModSaveFile(string filename);
bool loadModSaveFile(string filename);
extern const char* saveFileName;

typedef struct AlonWoofSaveData
{
	int magicNumber;
	char versionMajor;
	char versionMinor;
	bool tailsAltSkin = false;
	int shimaiTalkCount = 0;
};



#endif