
#include <SADXModLoader.h>
#include "pch.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include "world-location.h"

#include "LoadModel.h"

extern const HelperFunctions* helperFunctionsGlobal;

NJS_OBJECT* CreamObject;
WeightInfo* CreamWeights;

NJS_TEXNAME CreamTexName[10];
NJS_TEXLIST CreamTexlist = { arrayptrandlengthT(CreamTexName, unsigned int) };

NJS_MOTION* motion_Cream_fly;
NJS_ACTION action_Cream_fly;

bool test_creamLoaded = false;

DataPointer(float, CREAM_MOVE_SPEED, 0x8247A4);
DataPointer(float, CREAM_FLOAT_SPEED, 0x8247A8);



//Since there's only one, make it global.
// I don't give a heck.
int creamFrame = 0;

void LoadCreamFiles()
{
	LoadPVM("CREAM_NUDE", &CreamTexlist);

	CreamObject = LoadModel("system\\NudeCream.sa1mdl", CreamWeights);
	helperFunctionsGlobal->Weights->Init(CreamWeights, CreamObject);

	motion_Cream_fly = LoadAnimation("system\\Cream_Fly.saanim");
	action_Cream_fly.object = CreamObject;
	action_Cream_fly.motion = motion_Cream_fly;

	test_creamLoaded = true;
}

void NudeCream_Display(task* tp)
{
	taskwk* twp = tp->twp;

	if (!test_creamLoaded)
		LoadCreamFiles();

	if (!loop_count)
	{
		//ResetMaterial();
		njSetTexture(&CreamTexlist);
		___dsSetPalette(2);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);
		ROTATEZ(0, twp->ang.z);
		ROTATEX(0, twp->ang.x);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(180.0f));

		njScale(0, 1.5f, 1.5f, 1.5f);

		helperFunctionsGlobal->Weights->Apply(CreamWeights, &action_Cream_fly, creamFrame);
		dsDrawMotion(CreamObject, motion_Cream_fly, creamFrame);

		njPopMatrix(1u);
		___dsSetPalette(0);

		creamFrame += 2;

		if (creamFrame > 60)
			creamFrame = 0;


	}

	
}

void initNudeCream()
{
	WriteJump((void*)0x634F40, NudeCream_Display);
	CREAM_MOVE_SPEED = 1.25f;
	CREAM_FLOAT_SPEED = 0.25f;
}

void TestCreamTask(task* tp)
{

	if (!playertwp[0])
		return;

	tp->twp->pos = getPlayerSidePos(playertwp[0], 5.0f, 0);
	
	

	NudeCream_Display(tp);

}

task* createTestCreamTask()
{
	return CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, TestCreamTask);
}


