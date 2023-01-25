
#include "pch.h"
#include "helper-functions.h"
#include "body-functions.h"
#include "body-model.h"

#include "nudieSonic.h"
#include "nudieTails.h"
#include "nudieKnuckles.h"
#include "nudieAmy.h"
#include "nudieBig.h"

#include "nudieTikal.h"
#include "nudieKnuxTribe.h"

#include "jiggleTask.h"

#define ReplacePVM(a, b) helperFunctions.ReplaceFile("system\\" a ".PVM", "system\\" b ".PVM");



BodyState playerBodyStates[Characters_MetalSonic];
task * jiggleTasks[16];

NJS_OBJECT* Object_SonicTorso;
NJS_OBJECT* Object_KnucklesTorso;
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

void initBodySystem(const HelperFunctions& helperFunctions)
{

	//Boner killer
	for (int i = 0; i < Characters_MetalSonic; i++)
	{
		playerBodyStates[i] = E_Body_Normal;
	}

	//For some reason, just replacing the base PVM isn't enough for some of them.

	ReplacePVM("SONIC", "SONIC_NUDE");
	ReplacePVM("SONIC_DC", "SONIC_NUDE");

	ReplacePVM("SUPERSONIC", "SUPERSONIC_NUDE");
	ReplacePVM("SUPERSONIC_DC", "SUPERSONIC_NUDE");

	ReplacePVM("MILES", "MILES_NUDE");
	ReplacePVM("MILES_DC", "MILES_NUDE");

	ReplacePVM("KNUCKLES", "KNUCKLES_NUDE");
	ReplacePVM("KNUCKLES_DC", "KNUCKLES_NUDE");

	ReplacePVM("AMY", "AMY_NUDE");
	ReplacePVM("AMY_DC", "AMY_NUDE");

	ReplacePVM("BIG", "BIG_NUDE");
	ReplacePVM("BIG_DC", "BIG_NUDE");

	ReplacePVM("TIKAL", "TIKAL_NUDE");
	ReplacePVM("TIKAL_DC", "TIKAL_NUDE");

	//Like hell I'm typing all this out more than once.
	Object_SonicTorso = SONIC_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling;
	Object_KnucklesTorso = KNUCKLES_OBJECTS[0]->child->child->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling->sibling;
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

}


void setPlayerBodyModels()
{
	//Set all the player's nude bodies dynamically based on their current states

	//The fastest boy
	Object_SonicTorso->model = getNudeBody(&sonicBody, playerBodyStates[Characters_Sonic]);

	//Tails is the best boy ♥
	MILES_MODELS[0] = getNudeBody(&tailsBody, playerBodyStates[Characters_Tails]);
	MILES_MODELS[1] = getNudeBody(&tailsBodyFlying, playerBodyStates[Characters_Tails]);

	MILES_MODELS[14] = getNudeBody(&tailsBodyItem, playerBodyStates[Characters_Tails]);

	//Knuck Knuck its Knockles
	Object_KnucklesTorso->model = getNudeBody(&knucklesBody, playerBodyStates[Characters_Knuckles]);
	
	//Amy is the best girl ♥
	Object_AmyTorso->model = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);
	AMY_MODELS[3] = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);
	AMY_MODELS[4] = getNudeBody(&amyBody, playerBodyStates[Characters_Amy]);

	//Big fluffy cat sheath/balls is adorable and soft-looking
	Object_BigPelvis->model = getNudeBody(&bigBody, playerBodyStates[Characters_Big]);

}



void setOtherNudeModels()
{
	//Replace other non-dynamic models

	//Why would Zero put a dress on her? 
	Model_AmyEggRoboTorso = nudieamy_zero_attach;

	//By popular demand, the cinnamon roll herself ♥
	Model_TikalTorso = nudietikal_attach;
	Object_TikalSkirt.evalflags = NJD_EVAL_HIDE;

	//Fix Tikal's skirt welding to her torso. (oof)
	TikalWeldInfo[11].VertexPairCount = 0;
	TikalWeldInfo[12].VertexPairCount = 0;

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

	task* jiggle = CreateElementalTask(2, 0, PlayerJiggleProc);


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