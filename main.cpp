
#include "pch.h"
#include "body-functions.h"
#include "arousal.h"
#include "helper-functions.h"

bool has_DC_Characters = false;
bool has_Lantern_Engine = false;

int warningFrames = 300;

extern float deltaTime;
extern float arousalLevel[Characters_MetalSonic];



void showWarnings()
{
	if (!has_DC_Characters)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(0, 18), "Dreamcast Characters by ItsEasyActually is now a requirement.");
		DisplayDebugStringFormatted(NJM_LOCATION(0, 19), "Your game will probably crash without it. Do what you want though, I'm a mod DLL, not a cop.");
	}

	if (!has_Lantern_Engine && warningFrames > 0)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(0, 20), "Lantern Engine strongly reccomended.");
		warningFrames--;
	}
}

void doModuleChecks()
{
	HMODULE handle = GetModuleHandle(L"SA1_Chars");

	if (handle)
		has_DC_Characters = true;


	handle = GetModuleHandle(L"sadx-dc-lighting");

	if (handle)
		has_Lantern_Engine = true;
}

DataPointer(NJS_OBJECT*, SonicBody, 0x0056AD48);

int number = 0;

extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{

		doModuleChecks();
		initBodySystem(helperFunctions);
		initializeTheHorny();

	}

	__declspec(dllexport) void OnFrame()
	{
		//DisplayDebugStringFormatted(NJM_LOCATION(0, 2), "Time for cute boys~");
		showWarnings();

		updateBodyStates();
		setPlayerBodyModels();
		setOtherNudeModels();

		updateTime();
		fixPartnerCollisions();
	}


	__declspec(dllexport) ModInfo SADXModInfo = { 11 };
}