
#include "pch.h"
#include "shimai.h"
#include "shimai-data.h"
#include "shimai-msg.h"
#include "LoadModel.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include <lanternapi.h>
#include <stdio.h>

using namespace std;

#define GET_SHIMAIWK(tp) ((ShimaiWork*)tp->awp->work.ptr[0])
#define SHIMAIDATA(tp) shimaiData[((ShimaiWork*)tp->awp->work.ptr[0])->sisterID]

extern NJS_TEXLIST ShimaiTexlist;
extern NJS_OBJECT ShimaiShadow;
extern const HelperFunctions* helperFunctionsGlobal;
extern bool gDebugMode;
int gShimaiTalkCount = 0;
extern bool gHasDCCharacters;
extern bool gHasLanternEngine;

enum
{
	SHIMAI_MD_INIT,
	SHIMAI_MD_IDLE,
	SHIMAI_MD_TALK
};

const char* shimaiNameStr[] =
{
	"JENNY",
	"DEEJAY"
};

const char* shimaiModeStr[] =
{
	"SHIMAI_MD_INIT",
	"SHIMAI_MD_IDLE",
	"SHIMAI_MD_TALK"
};



CCL_INFO colli_info_shimai[1] =
{
	{ 0, CI_FORM_PERSON, CI_PUSH_PO_CMN | CI_PUSH_TH_CMN, 0, 0, { 0.0f, 1.0f, 0.0f}, 3.0f, 3.0f, 0.65f, 0.0f, 0, 0, 0 },
};

struct ShimaiWork
{
	char sisterID;

	ShimaiAnim* currentAnim;
	float animFrame;
	float animSpeed;
	
	ShimaiMessagePool* msgPool;

	NpcMessageMemory msgBuffer;
	int msgCounter;
	int act = 0;
	char mes_status;
};

static void loadShimaiAnimation(ShimaiAnim* animData, NJS_OBJECT* obj)
{

	NJS_MOTION* newMotion = new NJS_MOTION;

	string path;
	path += "system\\";
	path += animData->fileName;
	path += ".saanim";

	newMotion = LoadAnimation(path.c_str());
	animData->mAction->motion = newMotion;
	animData->mAction->object = obj;
}

bool shimaiMaterial(NJS_MATERIAL* material, Uint32 flags)
{
	set_diffuse(2, false);
	set_specular(8, false);

	return true;
}


const NJS_MATERIAL* matArray[] = { nullptr };

static void shimaiFixMaterials(NJS_OBJECT * obj)
{
	//Why wouldn't you tho
	if (!gHasLanternEngine)
		return;

	if (obj->basicdxmodel != nullptr)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			matArray[0] = &obj->basicdxmodel->mats[q];
			material_register(matArray, 1, &shimaiMaterial);
		}
	}

	if (obj->sibling != nullptr)
	{
		shimaiFixMaterials(obj->sibling);
	}

	if (obj->child != nullptr)
	{
		shimaiFixMaterials(obj->child);
	}
}

static void loadShimaiModel(ShimaiData* data)
{
	LoadPVM(data->shimaiPVMName, data->shimaiTexlist);

	string path;
	path += "system\\";
	path += data->shimaiModel;
	path += ".sa1mdl";

	data->shimaiObject = LoadModel(path.c_str(), data->shimaiWeightInfo);
	helperFunctionsGlobal->Weights->Init(data->shimaiWeightInfo, data->shimaiObject);


	shimaiFixMaterials(data->shimaiObject);

	loadShimaiAnimation(data->anim_idle, data->shimaiObject);
	loadShimaiAnimation(data->anim_talk, data->shimaiObject);
}

static void shimaiLoadMessagePool(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);
	shw->msgPool = NULL;

	switch (ssStageNumber)
	{
		case STAGE_SS_AFT:
			shw->msgPool = msgPool_ADVSS06[shw->sisterID];
			break;

		case STAGE_MR:
			shw->msgPool = msgPool_ADVSS06[shw->sisterID];
			break;

		case STAGE_EC_ST_AB:
			shw->msgPool = msgPool_ADVEC05[shw->sisterID];
			break;

		case STAGE_BEACH:
			shw->msgPool = msgPool_S01A02[shw->sisterID];
			break;

		case STAGE_CASINO:
			shw->msgPool = msgPool_S09A00[shw->sisterID];
			break;
	}

}

static void shimaiJennySetup(task* tp)
{

}

task* djShower = NULL;

static void shimaiDeeJaySetup(task* tp)
{
	SHIMAIDATA(tp).anim_idle = &anim_DeeJayIdle;
	SHIMAIDATA(tp).anim_talk = &anim_DeeJayIdle;

	if (ssStageNumber == STAGE_CASINO)
	{
		loadShimaiAnimation(&anim_DeeJayShower, SHIMAIDATA(tp).shimaiObject);
	}
	
} 


static void shimaiDeeJayExec(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (ssStageNumber == STAGE_CASINO && tp->twp->mode)
	{
		shw->currentAnim = &anim_DeeJayShower;
		shw->animSpeed = 0.5f;
	}
}

static void shimaiDestroy(task* tp)
{
	free(GET_SHIMAIWK(tp));
}

static void shimaiInit(task* tp)
{
	
	ShimaiWork * shw = GET_SHIMAIWK(tp);

	loadShimaiModel(&SHIMAIDATA(tp));
	shw->msgCounter = 0;
	shw->msgPool = NULL;
	shw->animFrame = 0;
	shw->animSpeed = 0.5f;
	shw->currentAnim = SHIMAIDATA(tp).anim_idle;

	switch (shw->sisterID)
	{
	case SHIMAI_JENNY:
		shimaiJennySetup(tp);
		break;

	case SHIMAI_DEEJAY:
		shimaiDeeJaySetup(tp);
		break;

	}

	shimaiLoadMessagePool(tp);
	CCL_Init(tp, colli_info_shimai, 1, CID_OBJECT);

}

static void drawShimaiShadow(task* tp)
{
	taskwk* twp = tp->twp;

	NJS_POINT3 a2;
	Angle3 a4;

	float y_off = twp->pos.y + 0.5f;

	float v6 = GetShadowPos(twp->pos.x, y_off, twp->pos.z, &a4) + 0.2f;
	if (v6 < y_off)
	{
		a2.y = v6;
		float v7 = y_off - v6;
		float v8 = twp->pos.z;
		a2.x = twp->pos.x;
		a2.z = v8;
		float thisa = 0.58f / (fabs(v7 + 1.0) * 0.05 + 1.0);
		njSetTexture(&ShimaiTexlist);
		njPushMatrix(0);
		njTranslateV(0, &a2);
		if (a4.z)
		{
			njRotateZ(0, LOWORD(a4.z));
		}
		if (a4.x)
		{
			njRotateX(0, LOWORD(a4.x));
		}
		njScale(0, thisa, thisa, thisa);
		ProcessModelNode_A_WrapperC(&ShimaiShadow, thisa);
		njPopMatrix(1u);
	}
}

static void shimaiDisp(task* tp)
{
	
	taskwk* twp = tp->twp;
	ShimaiWork* shw = GET_SHIMAIWK(tp);


	if (!loop_count)
	{
		ResetMaterial();
		njSetTexture(shimaiData[shw->sisterID].shimaiTexlist);
		//set_diffuse(8, false);
		___dsSetPalette(2u);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);

		ROTATEX(0, 0);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));
		ROTATEZ(0, 0);

		njScale(0, 1.0f, 1.0f, 1.0f);

		//placeholder static draw for now
		//dsDrawObject(shimaiData[shw->sisterID].shimaiObject);

		helperFunctionsGlobal->Weights->Apply(SHIMAIDATA(tp).shimaiWeightInfo, shw->currentAnim->mAction, GET_SHIMAIWK(tp)->animFrame);
		dsDrawMotion(SHIMAIDATA(tp).shimaiObject, shw->currentAnim->mAction->motion, GET_SHIMAIWK(tp)->animFrame);

		njPopMatrix(1u);
		___dsSetPalette(0);
	}

	drawShimaiShadow(tp);
}
static void shimaiDebug(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	njPrint((NJM_LOCATION(2, 8 + (8 * shw->sisterID))), "%s STATE: %s", shimaiNameStr[shw->sisterID], shimaiModeStr[tp->twp->mode]);
	njPrint((NJM_LOCATION(2, 9 + (8 * shw->sisterID))), " OBJECT: %x", SHIMAIDATA(tp).shimaiObject);
	njPrint((NJM_LOCATION(2, 10 + (8 * shw->sisterID))), " ANIM_IDLE: %x", SHIMAIDATA(tp).anim_idle->mAction);

}
static void startNPCMessage(task* tp, const char** msg)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	shw->msgBuffer.message_p = msg;
	shw->msgBuffer.flag_index = 0;

	NpcMessageStart(&shw->msgBuffer);
}
//Wait for player to close message.
static bool waitPlayerCloseMsg(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->mes_status == 0)
	{
		SetInputP(0, PL_OP_LETITGO);
		EV_MsgClose();
		return true;
	}

	playerpwp[0]->breathtimer = 0;

	return false;
}
//Check if player talks to us
static bool checkPlayerInteract(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);


	if (!shw->msgPool)
		return false;

	if (!shw->msgPool->msg_Character)
		return false;

	if (!shw->msgPool->msg_Character[0])
		return false;

	float dst = njDistanceP2P(&tp->twp->pos, &playertwp[0]->pos);
	float distThreshold = 10;

	if (CurrentCharacter == Characters_Big || CurrentCharacter == Characters_Gamma)
		distThreshold = 20;

	if (dst < distThreshold)
	{
		if (perG[0].press & (Buttons_B | Buttons_X))
		{
			SetInputP(0, PL_OP_PLACEON);
			HintRegistStatusPointer(&shw->mes_status);
			//startNPCMessage(tp, msg_Character[PLNO(playertwp[0])][jennywk->msgCounter]);

			startNPCMessage(tp, shw->msgPool->msg_Character[CurrentCharacter][shw->msgCounter]);
			

			if (!shw->msgCounter)
				shw->msgCounter++;

			return true;
		}
	}

	return false;
}
//Animation change
static void shimaiChangeAnimation(task* tp, ShimaiAnim* anim)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	shw->currentAnim = anim;
	shw->animFrame = 0;
}
//Check for mode changes
static void shimaiCheckMode(task* tp)
{
	if (!isIngame())
		return;

	ShimaiWork* shw = GET_SHIMAIWK(tp);

	switch (tp->twp->mode)
	{
	case SHIMAI_MD_INIT:
		break;

	case SHIMAI_MD_IDLE:
		if (checkPlayerInteract(tp))
		{
			tp->twp->mode = SHIMAI_MD_TALK;
			//changeJennyAction(tp, &action_Jenny_talk);
			shimaiChangeAnimation(tp, SHIMAIDATA(tp).anim_talk);
			shw->animSpeed = 0.75f;
			InputHookSet(tp, &tp->twp->pos, &tp->twp->ang.y, 0, 0, 10.0f);
			gShimaiTalkCount++;
		}
		return;

	case SHIMAI_MD_TALK:
		if (waitPlayerCloseMsg(tp))
		{
			tp->twp->mode = SHIMAI_MD_IDLE;
			//changeJennyAction(tp, &action_Jenny_idle);
			shimaiChangeAnimation(tp, SHIMAIDATA(tp).anim_idle);
		}
		break;
	}
}
//Cute idea also used in my Amy fangame
//Was inspired by your home gyroid in Animal Crossing
static void shimaiProximitySpeed(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	float minDist = 10;
	float maxDist = 50;

	float minAnimSpeed = 0.45f;
	float maxAnimSpeed = 1.25f;
	

	float dst = njDistanceP2P(&tp->twp->pos, &playertwp[0]->pos);

	float fac = clampFloat01(remapRange(dst, minDist, maxDist, 0.0f, 1.0f));

	//njPrint(NJM_LOCATION(16, 30 + shw->sisterID), "DIST: %f FAC: %f", dst, fac);

	shw->animSpeed = lerp(maxAnimSpeed, minAnimSpeed, fac);
}
//Main exec
static void shimaiExec(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->act != ssActNumber)
	{
		DestroyTask(tp);
		return;
	}

	switch (tp->twp->mode)
	{
	case SHIMAI_MD_INIT:
		shimaiInit(tp);
		tp->twp->mode++;
		break;

	case SHIMAI_MD_IDLE:
		shimaiProximitySpeed(tp);
		break;

	case SHIMAI_MD_TALK:
		break;
	}

	if (shw->sisterID == SHIMAI_DEEJAY)
		shimaiDeeJayExec(tp);

	GET_SHIMAIWK(tp)->animFrame += GET_SHIMAIWK(tp)->animSpeed;

	if (GET_SHIMAIWK(tp)->animFrame > GET_SHIMAIWK(tp)->currentAnim->mAction->motion->nbFrame)
		GET_SHIMAIWK(tp)->animFrame = 0;

	shimaiCheckMode(tp);


	if(gDebugMode)
		shimaiDebug(tp);

	shimaiDisp(tp);
	EntryColliList(tp->twp);
}

static bool shouldCreateSister(char sisterID)
{
	if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_SS_AFT)
		return false;

	if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_MR)
		return false;

	if (ssStageNumber == STAGE_EC_ST_AB && GetEventFlag((EventFlags)FLAG_KNUCKLES_EC_PALMSWITCH))
		return false;

	return true;
}
//Create Sisters~
static task* createSister(char sisterID)
{
	if (!shouldCreateSister(sisterID))
		return NULL;

	task* newSis = CreateElementalTask(IM_TASKWK | IM_ANYWK, LEV_3, shimaiExec);
	newSis->awp->work.ptr[0] = new ShimaiWork;

	ShimaiWork* shw = GET_SHIMAIWK(newSis);
	shw->sisterID = sisterID;
	shw->act = ssActNumber;

	newSis->exec = shimaiExec;
	newSis->disp = shimaiDisp;
	newSis->dest = shimaiDestroy;

	return newSis;
}

task* createJenny()
{
	return createSister(SHIMAI_JENNY);
}
task* createDeeJay()
{
	return createSister(SHIMAI_DEEJAY);
}