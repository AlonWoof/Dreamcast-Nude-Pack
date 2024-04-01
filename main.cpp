#include "pch.h"
#include "body-functions.h"
#include "arousal.h"
#include "helper-functions.h"
#include "amy_shower.h"
#include "CustomObjects.h"
#include <UsercallFunctionHandler.h>
#include <FunctionHook.h>

bool has_DC_Characters = false;
bool has_Lantern_Engine = false;

int warningFrames = 300;

extern float deltaTime;
extern float arousalLevel[Characters_MetalSonic];
const HelperFunctions* helperFunctionsGlobal;


void showWarnings()
{
	if (!has_DC_Characters)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(2, 18), "Dreamcast Characters by ItsEasyActually is now a requirement.");
		DisplayDebugStringFormatted(NJM_LOCATION(2, 19), "Your game will probably crash without it.");
		DisplayDebugStringFormatted(NJM_LOCATION(2, 20), "Do what you want though, I'm a mod DLL, not a cop.");
		
	}

	if (!has_Lantern_Engine && warningFrames > 0)
	{
		DisplayDebugStringFormatted(NJM_LOCATION(2, 22), "Lantern Engine strongly reccomended.");
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

FunctionHook <void> InitializeStage_h(0x415210);
FunctionHook <void> InitTask_h(0x40B460);

void InitializeStage_r()
{
	//calculateIncidentalArousal();
	InitializeStage_h.Original();
	setupAllCustomObjects();
}

void InitTask_r()
{
	InitTask_h.Original();
	
}


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

		doModuleChecks();
		initBodySystem(helperFunctions, path);
		initializeTheHorny();

		InitializeStage_h.Hook(InitializeStage_r);
		helperFunctionsGlobal = &helperFunctions;
	}

	__declspec(dllexport) void OnFrame()
	{
	
		showWarnings();

		updateBodyStates();
		setPlayerBodyModels();
		setOtherNudeModels();

		updateTime();
		//fixPartnerCollisions();

		//AMY_ACTIONS[24]
		amy_action[24].mtnmode = MD_MTN_STOP;
		amy_action[24].next = 25;

		if (playertwp[0] && !EV_CheckCansel())
		{
			checkIfShowerTime(0);
		}

	#ifdef DEBUG
		njPrint(NJM_LOCATION(0, 2), "Time for cute boys~");
		DBG_ShowArousalLevels();
	
		if (perG[0].press & Buttons_Up && isIngame())
		{
			//calculateIncidentalArousal();
			//createJiggleTasksForPlayer(0);
			//if(playertp[0])
			task * objTest = CreateElementalTask(IM_TASKWK, LEV_3, objectTestTask);
			objTest->twp->pos = playertwp[0]->pos;
			objTest->twp->pos.y += 10;
			objTest->twp->scl = { 1.0f, 1.0f, 1.0f };
			objTest->twp->counter.l = 1;
		}
	#endif // DEBUG

		//WriteJump((void*)0x00487810, &AmyCheckInput_ASM);
	}


	__declspec(dllexport) ModInfo SADXModInfo = { 11 };
}