#include "pch.h"
#include "body-functions.h"
#include "arousal.h"
#include "helper-functions.h"
#include "amy_shower.h"

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
#ifdef DEBUG
		njPrint(NJM_LOCATION(0, 2), "Time for cute boys~");
#endif // DEBUG

		
		showWarnings();

		updateBodyStates();
		setPlayerBodyModels();
		setOtherNudeModels();

		updateTime();
		fixPartnerCollisions();

		//AMY_ACTIONS[24]
		amy_action[24].mtnmode = MD_MTN_STOP;
		amy_action[24].next = 25;

		if (playertwp[0])
		{
			checkIfShowerTime(0);
		}

		if (perG[0].press & Buttons_Up)
		{
			//createJiggleTasksForPlayer(0);
			//if(playertp[0])
				
		}

		//WriteJump((void*)0x00487810, &AmyCheckInput_ASM);
	}


	__declspec(dllexport) ModInfo SADXModInfo = { 11 };
}