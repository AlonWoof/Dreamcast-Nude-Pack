#include "pch.h"
#include "body-functions.h"
#include "arousal.h"
#include "helper-functions.h"
#include "amy_shower.h"
#include "NudeCream.h"
#include "CustomObjects.h"
#include <UsercallFunctionHandler.h>
#include <FunctionHook.h>
#include "AlonWoofProductionsSave.h"

#include "IniFile.hpp"

//bool gHasDCCharacters = false;
//bool gHasLanternEngine = false;

HMODULE gDCCharactersHandle;
HMODULE gLanternEngineHandle;
HMODULE gDestinyIslandsHandle;


bool SonicEnabled = true;
bool TailsEnabled = true;
bool KnucklesEnabled = true;
bool AmyEnabled = true;
bool BigEnabled = true;

bool TailsAlt = false;

int warningFrames = 300;

extern float deltaTime;
extern float arousalLevel[Characters_MetalSonic];
const HelperFunctions* helperFunctionsGlobal;
bool gDebugMode = false;
extern int gShimaiTalkCount;


FunctionPointer(char, CreateCreamManager, (unsigned int idx), 0x635610);

TaskFunc(CreamManager, 0x6353A0);
TaskFunc(Cream, 0x635270);

DataPointer(char, flagCreamCreated, 0x3C83029);
DataPointer(char, flagKillCreamManager, 0x3C83028);

void showWarnings()
{
	if (!gDCCharactersHandle)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(2, 18), "Dreamcast Characters by ItsEasyActually is now a requirement.");
		DisplayDebugStringFormatted(NJM_LOCATION(2, 19), "Your game will probably crash without it.");
		DisplayDebugStringFormatted(NJM_LOCATION(2, 20), "Do what you want though, I'm a mod DLL, not a cop.");	
	}

	if (!gLanternEngineHandle && warningFrames > 0)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(2, 22), "Lantern Engine strongly reccomended.");
		warningFrames--;
	}
}

void doModuleChecks()
{
	gDCCharactersHandle = GetModuleHandle(L"SA1_Chars");
	gLanternEngineHandle = GetModuleHandle(L"sadx-dc-lighting");
	gDestinyIslandsHandle = GetModuleHandle(L"DestinyIslands");
	
}

//UsercallFunc(int, AmyCheckInput, (playerwk* pwp, motionwk2* mwp, taskwk* twp), (pwp, mwp, twp), 0x00487810, rEAX, rECX, rEDI, rESI);

#pragma region LoadingHooks
FunctionHook <void> InitializeStage_h(0x415210);
FunctionHook <void> InitTask_h(0x40B460);
FunctionHook <void, int> AdvanceActLocal_h(0x4146E0);

FunctionHook <void> GameInit_h(0x4159A0);
FunctionHook <void>  AL_SetObjectOnTheGarden_h(0x717BA0);

void AL_SetObjectOnTheGarden_r()
{
	AL_SetObjectOnTheGarden_h.Original();
	setupChaoGardenGirls();
}

void InitializeStage_r()
{
	//calculateIncidentalArousal();
	InitializeStage_h.Original();
	saveNudeModData();
	setupAllCustomObjects();
	calculateIncidentalArousal();
}

void AdvanceActLocal_r(int ssActAddition)
{
	AdvanceActLocal_h.Original(ssActAddition);
	saveNudeModData();
	setupAllCustomObjects();
	calculateIncidentalArousal();
}

void InitTask_r()
{
	InitTask_h.Original();
}

void GameInit_r()
{
	GameInit_h.Original();
	saveNudeModData();
	setupAllCustomObjects();
	calculateIncidentalArousal();
}
#pragma endregion



void objectTestTask_disp(task* tp)
{
	taskwk* twp = tp->twp;

	if (!loop_count)
	{

		ResetMaterial();

		njSetTexture(&KNUCKLES_TEXLIST);
		___dsSetPalette(2);

		njPushMatrix(0);

		njTranslateV(0, &twp->pos);
		ROTATEZ(0, twp->ang.z);
		ROTATEX(0, twp->ang.x);
		ROTATEY(0, twp->ang.y);
		njScale(0, 2.5f, 1.5f, 2.5f);

		ds_DrawObjectClip(KNUCKLES_OBJECTS[twp->counter.l], 1.0);

		njPopMatrix(1u);
	}
}

void objectTestTask(task * tp)
{
	if (ulGlobalTimer % 120 == 0)
		tp->twp->counter.l = !tp->twp->counter.l;

	njPrint(NJM_LOCATION(40, 40), "KNUCKLES OBJECT: %i", tp->twp->counter.l);
	objectTestTask_disp(tp);
}


extern "C"
{
	__declspec(dllexport) void Init(const char* path, const HelperFunctions& helperFunctions)
	{
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		SonicEnabled = config->getBool("MainChars", "SonicEnabled", true);
		TailsEnabled = config->getBool("MainChars", "TailsEnabled", true);
		TailsAlt = config->getBool("Bonus", "TailsAlt", false);
		KnucklesEnabled = config->getBool("MainChars", "KnucklesEnabled", true);
		AmyEnabled = config->getBool("MainChars", "AmyEnabled", true);
		BigEnabled = config->getBool("MainChars", "BigEnabled", true);

		for (int i = 0; i < getTimeSeconds(); i++)
		{
			random(0, getTimeSeconds());
		}

		doModuleChecks();
		initBodySystem(helperFunctions, path);
		initializeTheHorny();
		initNudeCream();

		//InitializeStage_h.Hook(InitializeStage_r);
		AdvanceActLocal_h.Hook(AdvanceActLocal_r);
		GameInit_h.Hook(GameInit_r);
		AL_SetObjectOnTheGarden_h.Hook(AL_SetObjectOnTheGarden_r);
		helperFunctionsGlobal = &helperFunctions;

		saveNudeModData();

	}



	__declspec(dllexport) void OnFrame()
	{

		showWarnings();

		updateBodyStates();
		setPlayerBodyModels();
		setOtherNudeModels();
		checkCustomObjects();

		updateTime();
		//fixPartnerCollisions();

		//AMY_ACTIONS[24]
		amy_action[24].mtnmode = MD_MTN_STOP;
		amy_action[24].next = 25;

		if (playertwp[0] && !EV_CheckCansel())
		{
			checkIfShowerTime(0);
		}

		if (KeyGetPress(PDD_KEYUS_F3))
			gDebugMode = !gDebugMode;

		if (KeyGetPress(PDD_KEYUS_F5))
			calculateIncidentalArousal();

		seqVars[FLAG_AMY_MR_APPEAR_FINALEGG] = 1;


		if (gDebugMode)
		{
			njPrint(NJM_LOCATION(3, 38), "gShimaiTalkCount: %i", gShimaiTalkCount);
			DBG_ShowArousalLevels();
		}

	}

	__declspec(dllexport) void OnExit()
	{
		//saveNudeModData();
	}

	__declspec(dllexport) ModInfo SADXModInfo = { 11 };
}