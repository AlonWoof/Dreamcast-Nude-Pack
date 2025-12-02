#include <SADXModLoader.h>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>   
#include "pch.h"
#include "AlonWoofProductionsSave.h"

using namespace std;

extern bool TailsAlt;

AlonWoofSaveData * currentSave;

const char * saveFileName = "NUDE";

void initSaveData()
{

	if(currentSave == nullptr)
		currentSave = new AlonWoofSaveData;

	currentSave->magicNumber = ALONWOOFMAGIC;
	currentSave->versionMajor = MOD_MAJOR_VERSION;
	currentSave->versionMinor = MOD_MINOR_VERSION;

	writeModSaveFile(saveFileName);
}

bool loadModSaveFile(string filename)
{
	currentSave = new AlonWoofSaveData;

	char* buf = nullptr;
	size_t sz = 0;

	if (_dupenv_s(&buf, &sz, "APPDATA") != 0 || buf == nullptr)
	{
		PrintDebug("Could not get environment variable!　\n");
		return false;
	}

	string path;
	path += buf;
	path += "\\..\\LocalLow\\Alonwoof Productions\\Sonic Adventure\\";
	path += filename + ".dat";

	fstream infile;

	infile.open(path, ios::in | ios::binary);

	if (!infile)
	{
		return false;
	}

	infile.read((char*)currentSave, sizeof(AlonWoofSaveData));
	infile.close();

	if (currentSave->magicNumber != (int)ALONWOOFMAGIC)
		return false;

	return true;
}

void writeModSaveFile(string filename)
{
	char* buf = nullptr;
	size_t sz = 0;

	if (_dupenv_s(&buf, &sz, "APPDATA") != 0 || buf == nullptr)
	{
		PrintDebug("Could not get environment variable!　\n");
		return;
	}

	string path;
	path += buf;

	path += "\\..\\LocalLow\\Alonwoof Productions\\";

	CreateDirectory(wstring(path.begin(), path.end()).c_str(), NULL);

	path += "Sonic Adventure\\";
	
	CreateDirectory(wstring(path.begin(), path.end()).c_str(), NULL);

	path += filename + ".dat";

	ofstream outfile;
	outfile.open(path, ios::out | ios::binary);

	if (!outfile)
	{
		PrintDebug("File path is invalid！ \n");
		return;
	}

	outfile.write((char*)currentSave, sizeof(AlonWoofSaveData));

	outfile.close();

}

void saveNudeModData()
{
	if (currentSave == nullptr)
	{
		if (!loadModSaveFile(saveFileName))
		{
			initSaveData();
		}
	}

	if (currentSave != nullptr)
	{
		//currentSave->numberVisits++;
		currentSave->tailsAltSkin = TailsAlt;
		writeModSaveFile(saveFileName);
	}
}

