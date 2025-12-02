
#include "pch.h"
#include "helper-functions.h"
#include "body-functions.h"
#include "body-model.h"

#include "nudieSonic.h"
#include "nudieTails.h"
#include "nudieTails-cunny.h"
#include "nudieKnuckles.h"
#include "nudieKnuxTribe.h"
#include "nudieAmy.h"
#include "nudieBig.h"

#include "nudieTikal.h"
#include "nudieKnuxTribe.h"

#include "jiggleTask.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");

extern bool SonicEnabled;
extern bool TailsEnabled;
extern bool KnucklesEnabled;
extern bool AmyEnabled;
extern bool BigEnabled;

extern bool TailsAlt;

BodyState playerBodyStates[Characters_MetalSonic];
task * jiggleTasks[16];

NJS_OBJECT* Object_SonicTorso;
NJS_OBJECT* Object_SuperSonicTorso;
NJS_OBJECT* Object_TailsTorso;
NJS_OBJECT* Object_KnucklesTorso;
NJS_OBJECT* Object_KnucklesTorsoFlying;
NJS_OBJECT* Object_AmyTorso;
NJS_OBJECT* Object_BigPelvis;

NJS_OBJECT* Object_TR1SonicTorso;
NJS_OBJECT* Object_TR2BeforeSonicTorso;
NJS_OBJECT* Object_TR2ChangeSonicTorso;

NJS_OBJECT* Object_TR2SonicTorso;

NJS_OBJECT* Object_EV_TR1SonicTorso;
NJS_OBJECT* Object_EV_TR2BeforeSonicTorso;

NJS_OBJECT* Object_EV_TR1DestroyedSonicTorso;
NJS_OBJECT* Object_EV_TR2TransformingSonicTorso;
NJS_OBJECT* Object_EV_TR2ChangeSonicTorso;

DataPointer(NJS_MODEL_SADX, Model_AmyEggRoboTorso, 0x03197354);

DataPointer(NJS_OBJECT, Object_TikalSkirt, 0x008D24C4);
DataPointer(NJS_MODEL_SADX, Model_TikalTorso, 0x008D4784);



DataPointer(NJS_OBJECT, tr2b_s_tru2_body, 0x2EE9D28);

HMODULE handle = GetModuleHandle(L"ADV03MODELS");
NJS_OBJECT** ___ADV03_OBJECTS = (NJS_OBJECT**)GetProcAddress(handle, "___ADV03_OBJECTS");


int tornado1_objectOffsets[] =
{
	0x0028B7A0C,0x0028BA71C,0x0028BDDBC,0x0028C09FC
};

/*
WriteData((NJS_OBJECT**)0x0028B7A0C, &Tornado1_Object);
WriteData((NJS_OBJECT**)0x0028BA71C, &Tornado1_Object);
WriteData((NJS_OBJECT**)0x0028BDDBC, &Tornado1_Object);
WriteData((NJS_OBJECT**)0x0028C09FC, &Tornado1_Object);
*/


//Thanks Claire, love you <3

void makeModelColorWhite(NJS_MODEL_SADX * mdl)
{

	for (int i = 0; i < mdl->nbMat; i++)
	{
		mdl->mats[i].diffuse.color = 0xFFFFFFFF;
	}

}

void clearJiggleTasks()
{
	for (int i = 0; i < 16; i++)
	{
		if (jiggleTasks[i])
		{
			DestroyTask(jiggleTasks[i]);
			jiggleTasks[i] = 0;
		}
	}
}


void createJiggleTasksForPlayer(int pnum)
{
	int playerID = PLNO(playertwp[pnum]);
	
	switch (playerID)
	{

	case Characters_Sonic:
		addJigglePhysics(&sonicBody,pnum);
		break;

	case Characters_Tails:
		addJigglePhysics(&tailsBody, pnum);
		addJigglePhysics(&tailsBodyFlying, pnum);
		break;

	case Characters_Knuckles:
		addJigglePhysics(&knucklesBody, pnum);
		break;

	case Characters_Amy:
		addJigglePhysics(&amyBody, pnum);
		break;

	case Characters_Big:
		addJigglePhysics(&bigBody, pnum);
		break;

	}
}

NJS_MODEL_SADX * getNudeBody(BodyModel* model, BodyState state)
{
	NJS_MODEL_SADX* mBod;

	switch (state)
	{
		case E_Body_Aroused:
			mBod = model->body_Aroused;
			break;
		case E_Body_Cold:
			mBod = model->body_Cold;
			break;
		default:
			mBod = model->body_Normal;
			break;
	}

	return mBod;
}

JiggleWeightInfo * getBodyJiggleInfo(BodyModel* model)
{
	return model->body_Normal_JiggleInfo;
}

int getBodyJiggleSize(BodyModel* model)
{
	return model->bodyJiggleSize;
}

void setBodyModelWhite(BodyModel* model)
{
	makeModelColorWhite(model->body_Normal);
	makeModelColorWhite(model->body_Aroused);
	makeModelColorWhite(model->body_Cold);
}

void initBodySystem(const HelperFunctions& helperFunctions, const char* path)
{

	//Boner killer
	for (int i = 0; i < Characters_MetalSonic; i++)
	{
		playerBodyStates[i] = E_Body_Normal;
	}

	//For some reason, just replacing the base PVM isn't enough for some of them.

	//ReplacePVM("SONIC", "SONIC_NUDE");
	//ReplacePVM("SONIC_DC", "SONIC_NUDE");

	//ReplacePVM("SUPERSONIC", "SUPERSONIC_NUDE");
	//ReplacePVM("SUPERSONIC_DC", "SUPERSONIC_NUDE");

	if (TailsEnabled)
	{
		ReplacePVM("MILES", "MILES_NUDE");
		ReplacePVM("MILES_DC", "MILES_NUDE");
	}

	//ReplacePVM("KNUCKLES", "KNUCKLES_NUDE");
	//ReplacePVM("KNUCKLES_DC", "KNUCKLES_NUDE");

	if (AmyEnabled)
	{
		ReplacePVM("AMY", "AMY_NUDE");
		ReplacePVM("AMY_DC", "AMY_NUDE");
	}

	if (BigEnabled)
	{
		ReplacePVM("BIG", "BIG_NUDE");
		ReplacePVM("BIG_DC", "BIG_NUDE");
	}

	ReplacePVM("TIKAL", "TIKAL_NUDE");
	ReplacePVM("TIKAL_DC", "TIKAL_NUDE");

	if (AmyEnabled)
	{
		//Zero with Amy
		ReplacePVM("AMY_EGGROBO", "AMY_EGGROBO_NUDE");
		ReplacePVM("AMY_EGGROBO_DC", "AMY_EGGROBO_NUDE");
	}

	//Mission mode objects
	ReplacePVM("MISSION", "MISSION_NUDE");

	//Gamma memories
	if (AmyEnabled)
		helperFunctions.ReplaceTexture("ICM00C3", "SNAP005", (std::string(path) + "//textures/SNAP005.png").c_str(), 600913, 256, 256);

	//Life icons
	helperFunctions.ReplaceTexture("CON_REGULAR_E", "hyoji_zanki_a", (std::string(path) + "//textures/hyoji_zanki_a.png").c_str(), 999002, 256, 256);
	helperFunctions.ReplaceTexture("CON_REGULAR", "hyoji_zanki_a", (std::string(path) + "//textures/hyoji_zanki_a.png").c_str(), 999002, 256, 256);

	// Ending stuff coming soon.
	// I just need to take ALL of the screenshots
	// ...
	// And remake the end screen renders.
	// Hoo boy.... I bit off more than I can chew, huh?


	if (SonicEnabled)
	{
		//Sonic credits sequence
		ReplacePVM("ENDBG_SONIC_0", "ENDBG_SONIC_0_NUDE");
		ReplacePVM("ENDBG_SONIC_1", "ENDBG_SONIC_1_NUDE");
		ReplacePVM("ENDBG_SONIC_2", "ENDBG_SONIC_2_NUDE");
	}

	if (TailsEnabled)
	{
		if (!TailsAlt)
		{
			//Tails credits sequence
			ReplacePVM("ENDBG_TAILS_0", "ENDBG_TAILS_0_NUDE");
			ReplacePVM("ENDBG_TAILS_1", "ENDBG_TAILS_1_NUDE");
			ReplacePVM("ENDBG_TAILS_2", "ENDBG_TAILS_2_NUDE");
		}
		else
		{
			//Trans Tails version
			ReplacePVM("ENDBG_TAILS_0", "ENDBG_TAILS_0_CUNNY");
			ReplacePVM("ENDBG_TAILS_1", "ENDBG_TAILS_1_CUNNY");
			ReplacePVM("ENDBG_TAILS_2", "ENDBG_TAILS_2_CUNNY");
		}
	}


	if (KnucklesEnabled)
	{
		//Knuckles credits sequence
		ReplacePVM("ENDBG_KNUCKLES_0", "ENDBG_KNUCKLES_0_NUDE");
		ReplacePVM("ENDBG_KNUCKLES_1", "ENDBG_KNUCKLES_1_NUDE");
		ReplacePVM("ENDBG_KNUCKLES_2", "ENDBG_KNUCKLES_2_NUDE");
	}

	if (AmyEnabled)
	{
		//Amy credits sequence
		ReplacePVM("ENDBG_AMY_0", "ENDBG_AMY_0_NUDE");
		ReplacePVM("ENDBG_AMY_1", "ENDBG_AMY_1_NUDE");
		ReplacePVM("ENDBG_AMY_2", "ENDBG_AMY_2_NUDE");
		ReplacePVM("ENDBG_LAST_AMY", "ENDBG_LAST_AMY_NUDE");

		//Amy Summary
		ReplacePVM("SMRYBG_AMY", "SMRYBG_AMY_NUDE");
	}
	

	//Like hell I'm typing all this out more than once.
	Object_SonicTorso = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling;
	Object_SuperSonicTorso = SONIC_OBJECTS[22]->child->child->sibling->sibling->sibling->sibling;
	Object_TailsTorso = MILES_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_KnucklesTorso = KNUCKLES_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_KnucklesTorsoFlying = KNUCKLES_OBJECTS[1]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_AmyTorso = AMY_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_BigPelvis = BIG_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling;

	Object_TR1SonicTorso = (*((NJS_OBJECT**)0x0028B7A0C))->child->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_TR2BeforeSonicTorso = (*((NJS_OBJECT**)0x0027EFDDC))->child->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_TR2ChangeSonicTorso = (*((NJS_OBJECT**)0x00280F23C))->child->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;

	Object_EV_TR1SonicTorso = (**((NJS_OBJECT***)0x006BEE81))->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	//Object_EV_TR2BeforeSonicTorso = (**((NJS_OBJECT***)0x006B9281))->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_EV_TR2BeforeSonicTorso = (**((NJS_OBJECT***)0x006B9281))->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	

	Object_EV_TR1DestroyedSonicTorso = (*((NJS_OBJECT**)0x002935DFC))->child->child->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_EV_TR2TransformingSonicTorso = (*((NJS_OBJECT**)0x0028988FC))->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
	Object_EV_TR2ChangeSonicTorso = (*((NJS_OBJECT**)0x032ECE0C))->child->sibling->sibling->sibling->sibling->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling;


	//Fix for NPCs
	setBodyModelWhite(&sonicBody);
	setBodyModelWhite(&superSonicBody);
	setBodyModelWhite(&tailsBody);
	setBodyModelWhite(&tailsBody_cunny);
	setBodyModelWhite(&tailsBodyFlying);
	setBodyModelWhite(&tailsBodyItem);
	setBodyModelWhite(&knucklesBody);
	setBodyModelWhite(&amyBody);
	setBodyModelWhite(&bigBody);

}


void setPlayerBodyModels()
{
	//Set all the player's nude bodies dynamically based on their current states


	if (SonicEnabled)
	{
		//The fastest boy
		Object_SonicTorso->model = getNudeBody(&sonicBody, playerBodyStates[Characters_Sonic]);
	

		//SUPER fast now
		Object_SuperSonicTorso->model = getNudeBody(&superSonicBody, playerBodyStates[Characters_Sonic]);
	}

	if(TailsEnabled)
	{
		//Tails is the best boy ♥

		//DEBUG
		//if (ulGlobalTimer % 30 == 0)
		//	TailsAlt = !TailsAlt;

		if (TailsAlt)
		{
			Object_TailsTorso->model = getNudeBody(&tailsBody_cunny, playerBodyStates[Characters_Tails]);
			MILES_MODELS[0] = getNudeBody(&tailsBody_cunny, playerBodyStates[Characters_Tails]);
			MILES_MODELS[1] = getNudeBody(&tailsBody_cunny, playerBodyStates[Characters_Tails]);

			MILES_MODELS[14] = getNudeBody(&tailsBodyItem_cunny, playerBodyStates[Characters_Tails]);
		}
		else
		{
			Object_TailsTorso->model = getNudeBody(&tailsBody, playerBodyStates[Characters_Tails]);
			MILES_MODELS[0] = getNudeBody(&tailsBody, playerBodyStates[Characters_Tails]);
			MILES_MODELS[1] = getNudeBody(&tailsBodyFlying, playerBodyStates[Characters_Tails]);

			MILES_MODELS[14] = getNudeBody(&tailsBodyItem, playerBodyStates[Characters_Tails]);
		}
	}

	if (KnucklesEnabled)
	{
		//Knuck Knuck its Knockles
		Object_KnucklesTorso->model = getNudeBody(&knucklesBody, playerBodyStates[Characters_Knuckles]);
		Object_KnucklesTorsoFlying->model = getNudeBody(&knucklesBody, playerBodyStates[Characters_Knuckles]);
	}

	if (AmyEnabled)
	{
		//Amy is the best girl ♥
		Object_AmyTorso->model = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);
		AMY_MODELS[3] = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);
		AMY_MODELS[4] = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);
	}

	if (BigEnabled)
	{
		//Big fluffy cat sheath/balls is adorable and soft-looking
		Object_BigPelvis->model = getNudeBody(&bigBody, playerBodyStates[Characters_Big]);
	}

}



void setOtherNudeModels()
{
	//Replace other non-dynamic models

	if (AmyEnabled)
	{
		//Why would Zero put a dress on her? 
		Model_AmyEggRoboTorso = nudieamy_zero_attach;
	}

	//By popular demand, the cinnamon roll herself ♥
	Model_TikalTorso = nudietikal_attach;
	Object_TikalSkirt.evalflags = NJD_EVAL_HIDE;

	//Fix Tikal's skirt welding to her torso. (oof)
	TikalWeldInfo[11].VertexPairCount = 0;
	TikalWeldInfo[12].VertexPairCount = 0;

	if (SonicEnabled)
	{
		//So many damn skychase models. Let me know if I missed any.
		Object_TR1SonicTorso->model = &nudieSonic_TR1;
		Object_TR2BeforeSonicTorso->model = &nudieSonic_TR1;
		Object_TR2ChangeSonicTorso->model = &nudieSonic_TR1;
		Object_EV_TR1SonicTorso->model = &EV_nudieSonic_TR1;
		Object_EV_TR1DestroyedSonicTorso->model = &EV_nudieSonic_TR1_Destroyed;

		Object_EV_TR2BeforeSonicTorso->model = &EV_nudieSonic_TR2Before;
		Object_EV_TR2TransformingSonicTorso->model = &EV_nudieSonic_TR2Transforming;
		Object_EV_TR2ChangeSonicTorso->model = &EV_nudieSonic_TR2Change;
	}

	//Enchilada tribe. Yummy. 
	___ADV03_OBJECTS[3]->child->child->child->model = &nudieknuxfam_003;
	___ADV03_OBJECTS[5]->child->child->child->model = &nudieknuxfam_005;
	___ADV03_OBJECTS[6]->child->child->child->model = &nudieknuxfam_006;

}


// Who knows if I'll ever finish adding this functionality...
// I should honestly re-write it now that I know a lot more about tasks.
void addJigglePhysics(BodyModel * model, int pno)
{
	task* pl = EV_GetPlayer(pno);

	if (!pl)
		return;

	if (!playertwp[pno])
	{
		return;
	}

	bool foundEmptySpot = false;
	int slot = 0;

	for (int i = 0; i < 16; i++)
	{
	
		if (!jiggleTasks[i])
		{
			slot = i;
			foundEmptySpot = true;
			break;
		}
	}

	if (!foundEmptySpot)
		return;

	task* jiggle = CreateElementalTask(IM_TASKWK | IM_ANYWK | IM_MOTIONWK, 0, PlayerJiggleProc);


	if (!jiggle)
	{
		return;
	}

	jiggleTasks[slot] = jiggle;

	JiggleWeightInfo * info = getBodyJiggleInfo(model); 
	
	int infoSize = model->bodyJiggleSize;


	NJS_POINT3* originalPoints = copyPointsData(model->body_Normal);

	jiggle->awp = (anywk*)malloc(sizeof(anywk));

	jiggle->twp->mode = pno;
	jiggle->awp->work.sl[1] = infoSize;
	jiggle->awp->work.ptr[2] = model->body_Normal;
	jiggle->awp->work.ptr[3] = info;
	jiggle->awp->work.ptr[4] = originalPoints;

	PrintDebug("\nSIZE OF JIGGLE INFO: %i\n", jiggle->awp->work.sl[1]);


	jiggle->mwp = (motionwk*)malloc(sizeof(motionwk));

	jiggle->mwp->acc.x = 0.0f;
	jiggle->mwp->acc.y = 0.0f;
	jiggle->mwp->acc.z = 0.0f;


}