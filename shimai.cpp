
#include "pch.h"
#include "shimai.h"
#include "shimai-data.h"
#include "shimai-msg.h"
#include "LoadModel.h"
#include "helper-functions.h"
#include "decomp-functions.h"
#include <stdio.h>
#include <math.h>
#include <ctime>

using namespace std;

#define GET_SHIMAIWK(tp) ((ShimaiWork*)tp->awp->work.ptr[0])
#define SHIMAIDATA(tp) shimaiData[((ShimaiWork*)tp->awp->work.ptr[0])->sisterID]

extern NJS_TEXLIST ShimaiTexlist;
extern NJS_OBJECT ShimaiShadow;
extern const HelperFunctions* helperFunctionsGlobal;
extern bool gDebugMode;
int gShimaiTalkCount = 0;
extern HMODULE gLanternEngineHandle;

enum
{
	SHIMAI_MD_INIT,
	SHIMAI_MD_IDLE,
	SHIMAI_MD_TALK
};

const char* shimaiNameStr[] =
{
	"JENNY",
	"DEEJAY",
	"JENNY"
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

static int maskAnimTexID[] =
{
	17,18,19,20
};

static Uint32 maskAnimPtr[4] =
{
	NULL,
	NULL,
	NULL,
	NULL
};

struct ShimaiWork
{
	SHIMAI_ID sisterID;

	SHIMAI_MTN currentAnim;

	float animFrame;
	float animSpeed;

	int homeAngle;

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
	if (!gLanternEngineHandle)
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

static NJS_MATERIAL* jennyMaskMat;

static NJS_MATERIAL* shimaiGetMaskMaterial(NJS_OBJECT* obj, Uint32 texID)
{

	if (obj->basicdxmodel != nullptr)
	{
		for (int q = 0; q < obj->basicdxmodel->nbMat; ++q)
		{
			PrintDebug(" ATTR_TEXID: %i\n", obj->basicdxmodel->mats[q].attr_texId);

			if ( obj->basicdxmodel->mats[q].attr_texId == texID)
				return &obj->basicdxmodel->mats[q];

			//obj->basicdxmodel->mats[q].attr_texId = 0;
		}
	}

	NJS_MATERIAL* ret = NULL;

	if (obj->sibling != nullptr)
	{
		ret = shimaiGetMaskMaterial(obj->sibling, texID);
	}

	if (obj->child != nullptr)
	{
		ret = shimaiGetMaskMaterial(obj->child, texID);
	}

	if (ret)
		return ret;

	return NULL;
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
	jennyMaskMat = shimaiGetMaskMaterial(data->shimaiObject, 17);

	for (int i = 0; i < data->nbAnims; i++)
	{
		loadShimaiAnimation(&data->shimaiAnims[i], data->shimaiObject);
		data->shimaiAnims[i].mAction->object = data->shimaiObject;
	}

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

//Animation change
static void shimaiChangeAnimation(task* tp, SHIMAI_MTN newAnim)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (shw->currentAnim == newAnim)
		return;

	shw->currentAnim = newAnim;
	shw->animFrame = 0;
	
}

static void shimaiJennySetup(task* tp)
{

}

task* djShower = NULL;

static void shimaiDeeJaySetup(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	//SHIMAIDATA(tp).anim_idle = &anim_DeeJayIdle;
	//SHIMAIDATA(tp).anim_talk = &anim_DeeJayIdle;

	if (ssStageNumber == STAGE_CASINO)
	{
		shimaiChangeAnimation(tp, SHIMAI_MTN_SHOWERING);
	}
	
} 


static void shimaiDeeJayExec(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	if (ssStageNumber == STAGE_CASINO && tp->twp->mode)
	{
		shimaiChangeAnimation(tp, SHIMAI_MTN_SHOWERING);
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
	shw->currentAnim = SHIMAI_MTN_IDLE;
	shw->homeAngle = tp->twp->ang.y;

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


	tp->awp->work.ub[11]++;

	if (tp->awp->work.ub[11] > 15)
	{
		tp->awp->work.ub[10]++;
		tp->awp->work.ub[11] = 0;
	}

	if (tp->awp->work.ub[10] > 3)
		tp->awp->work.ub[10] = 0;
	
	if(jennyMaskMat)
		jennyMaskMat->attr_texId = 17 + tp->awp->work.ub[10];

	if (!loop_count)
	{
		ResetMaterial();
		njSetTexture(shimaiData[shw->sisterID].shimaiTexlist);
		//set_diffuse(8, false);
		___dsSetPalette(0);

		SaveControl3D();
		njControl3D(NJD_CONTROL_3D_CONSTANT_MATERIAL);
		SetMaterial(0.5f, 1.0f, 1.0f, 1.0f);

		njPushMatrix(0);
		njTranslateV(0, &twp->pos);

		ROTATEX(0, 0);
		ROTATEY(0, twp->ang.y + NJM_DEG_ANG(270.0f));
		ROTATEZ(0, 0);

		njScale(0, 1.0f, 1.0f, 1.0f);

		helperFunctionsGlobal->Weights->Apply(SHIMAIDATA(tp).shimaiWeightInfo, &SHIMAIDATA(tp).shimaiActions[shw->currentAnim], GET_SHIMAIWK(tp)->animFrame);
		dsDrawMotion(SHIMAIDATA(tp).shimaiObject, SHIMAIDATA(tp).shimaiActions[shw->currentAnim].motion, shw->animFrame);


		njPopMatrix(1u);
		ResetMaterial();
		LoadControl3D();
		___dsSetPalette(0);
	}

	drawShimaiShadow(tp);
}
static void shimaiDebug(task* tp)
{
	ShimaiWork* shw = GET_SHIMAIWK(tp);

	//njPrint((NJM_LOCATION(2, 8 + (8 * shw->sisterID))), "%s STATE: %s", shimaiNameStr[shw->sisterID], shimaiModeStr[tp->twp->mode]);
	//njPrint((NJM_LOCATION(2, 9 + (8 * shw->sisterID))), " OBJECT: %x", SHIMAIDATA(tp).shimaiObject);
	//njPrint((NJM_LOCATION(2, 10 + (8 * shw->sisterID))), " ANIM_IDLE: %x", SHIMAIDATA(tp).anim_idle->mAction);

	for (int i = 0; i < 32; i++)
	{
		if (&SHIMAIDATA(tp).shimaiActions[i] != NULL)
		{
			njPrint(NJM_LOCATION((30 * shw->sisterID) + 5, 50 + i), "ACTION %i OFFSET: %x", i, SHIMAIDATA(tp).shimaiActions[i].motion);
		}
	}

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

			if(shw->sisterID == SHIMAI_JENNY)
				shimaiChangeAnimation(tp, SHIMAI_MTN_TALK);

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
			shimaiChangeAnimation(tp, SHIMAI_MTN_IDLE);
		}
		break;
	}
}

unsigned int ShimaiGetAngleToTarget(NJS_POINT3* ps, NJS_POINT3* pd, float* dist, float* distxz)
{
	long double v5; // st7
	long double v6; // st6
	float v8; // [esp+8h] [ebp+8h]

	v5 = pd->x - ps->x;
	v8 = pd->y - ps->y;
	v6 = pd->z - ps->z;
	if (dist)
	{
		*dist = sqrt(v6 * v6 + v8 * v8 + v5 * v5);
	}
	if (distxz)
	{
		*distxz = sqrt(v6 * v6 + v5 * v5);
	}
	return (atan2(v6, -v5) * 65536.0 * 0.1591549762031479);
}

static void shimaiLerpAngle(task* tp, int targetAngle)
{

	int angle = tp->twp->ang.y;

	angle = lerp(angle, targetAngle, 0.2f);

	tp->twp->ang.y = angle;
}

static float fixAngle(float angle)
{
	while (angle > 360.0f)
		angle -= 360.0f;

	while (angle < 0)
		angle += 360.0f;

	return angle;
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
		shimaiLerpAngle(tp, shw->homeAngle);
		shimaiProximitySpeed(tp);
		break;

	case SHIMAI_MD_TALK:
		if(shw->sisterID == SHIMAI_JENNY)
			shimaiLerpAngle(tp, NJM_DEG_ANG(fixAngle(NJM_ANG_DEG(ShimaiGetAngleToTarget(&tp->twp->pos, &playertwp[0]->pos, 0, 0)) - NJM_DEG_ANG(180.0f))));
		break;
	}

	if (shw->sisterID == SHIMAI_DEEJAY)
		shimaiDeeJayExec(tp);

	GET_SHIMAIWK(tp)->animFrame += GET_SHIMAIWK(tp)->animSpeed;

	//if (GET_SHIMAIWK(tp)->animFrame > GET_SHIMAIWK(tp)->currentAnim->mAction->motion->nbFrame)
	//	GET_SHIMAIWK(tp)->animFrame = 0;

	shimaiCheckMode(tp);


	if(gDebugMode)
		shimaiDebug(tp);

	shimaiDisp(tp);
	EntryColliList(tp->twp);
}

static bool shouldCreateSister(char sisterID)
{
	if (sisterID != SHIMAI_JENNY_MAHOUSHOJO)
	{
		if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_SS_AFT)
			return false;

		if (GetTimeOfDay() == TimesOfDay_Night && ssStageNumber == STAGE_MR)
			return false;
	}
	else
	{

		//No witch hunting on school nights young lady
		if (getDayOfWeek() < WDAY_KIN)
			return false;

		if (GetTimeOfDay() != TimesOfDay_Night && ssStageNumber == STAGE_SS_AFT)
			return false;

		if (GetTimeOfDay() != TimesOfDay_Night && ssStageNumber == STAGE_MR)
			return false;
	}



	if (ssStageNumber == STAGE_EC_ST_AB && GetEventFlag((EventFlags)FLAG_KNUCKLES_EC_PALMSWITCH))
		return false;

	if (ssStageNumber == STAGE_BEACH)
	{
		int day = getDayOfWeek();

		//DeeJay's line about having school tomorrow won't make sense if it's not a school night.
		if (day == WDAY_KIN || day == WDAY_DO)
			return false;
	}

	return true;
}
//Create Sisters~
static task* createSister(SHIMAI_ID sisterID)
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
task* createJenny_MahouShojo()
{
	return createSister(SHIMAI_JENNY_MAHOUSHOJO);
}